#include "SimulationEngine.h"
#include "Player.h"
#include "PlayState.h"
#include <vector>
#include "Ball.h"
#include "Roster.h"

using namespace std;
using namespace simulation;


bool IncrementPlay(PlayState* state) 
{
	bool fPlayIsOver = false;
	for(vector<BasePlayer*>::iterator itPlayer = state->BeginPlayers(); itPlayer != state->EndPlayers(); itPlayer++)
	{
        if ((*itPlayer)->UpdatePlayer(state->GetBall()))
			fPlayIsOver = true;
        if ((*itPlayer)->HasBall())
            state->GetBall().UpdateLocation((*itPlayer)->GetLocation());
	}
    state->GetBall().IncrementLocation();
	return fPlayIsOver;
}

PlayState* InitialisePlayState(vector<Route*>& routes)
{
	PlayState* state = new PlayState();
	WideReceiver* pl1 = new WideReceiver(make_pair(30, 130), 1);
    vector<WideReceiver*> rgWr;
    rgWr.push_back(pl1);
    Quarterback* pl2 = new Quarterback(make_pair(30, 80), 1, rgWr);
    pl1->AssignRoute(routes[0]);
	state->AddPlayer(pl1);
    state->AddPlayer(pl2);
    Ball* bl = new Ball(Location(0,0), 0, 0);
    state->AddBall(bl);

	return state;
}

vector<Route*> GenerateRoutes()
{
	pair<double, double> start(0, 0);
	pair<double, double> intermediate(80, 0);
	pair<double, double> end(160, -40);
	RouteWaypoints waypoints;
	waypoints.push_back(start);
	waypoints.push_back(intermediate);
	waypoints.push_back(end);

	vector<Route*> routes;

	routes.push_back(new Route("Test", waypoints));

	return routes;
}

Play GeneratePlay()
{
	Play new_play = Play();

	vector<Route*> routes = GenerateRoutes();

	bool fPlayOver = false;
	PlayState* currentState = InitialisePlayState(routes);
	Frame* frame = new Frame(*currentState);
	new_play.push_back(frame);

	while (!fPlayOver) {
		fPlayOver = IncrementPlay(currentState);
		Frame* frame = new Frame(*currentState);
		new_play.push_back(frame);
	}

	return new_play;
}

bool simulation::SimulateGame(Game& simmedGame) 
{
	// load team rosters
	Roster rs_A = Roster();
	Roster rs_B = Roster();
	// load team game plans
	// GamePlan gp_A = Gameplan();
	// GamePlan gp_B = Gameplan();

	bool gameFinished = false;
	//game state should be tracked here

	while (!gameFinished)
	{
		//select a play based on game state
		
		Play nextPlay = GeneratePlay();
		simmedGame.push_back(nextPlay);
		gameFinished = true;
	}

	return true;
}