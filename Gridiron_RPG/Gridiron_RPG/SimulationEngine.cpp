#include "SimulationEngine.h"
#include "Player.h"
#include "PlayState.h"
#include <vector>

using namespace std;
using namespace simulation;


bool IncrementPlay(PlayState* state) 
{
	bool fPlayIsOver = false;
	for(vector<BasePlayer*>::iterator itPlayer = state->BeginPlayers(); itPlayer != state->EndPlayers(); itPlayer++)
	{
        if ((*itPlayer)->UpdatePlayer())
			fPlayIsOver = true;
	}
	return fPlayIsOver;
}

PlayState* InitialisePlayState(vector<Route*>& routes)
{
	PlayState* state = new PlayState();
	WideReceiver* pl1 = new WideReceiver(make_pair(30, 130), 1);
    Quarterback* pl2 = new Quarterback(make_pair(30, 80), 1);
    pl1->AssignRoute(routes[0]);
	state->AddPlayer(pl1);
    state->AddPlayer(pl2);

	return state;
}

void GeneratePlay(Play& generatedPlay, vector<Route*>& routes)
{
	bool fPlayOver = false;
	PlayState* currentState = InitialisePlayState(routes);
	Frame* frame = new Frame(*currentState);
	generatedPlay.push_back(frame);

	while (!fPlayOver) {
		fPlayOver = IncrementPlay(currentState);
		Frame* frame = new Frame(*currentState);
		generatedPlay.push_back(frame);
	}
}

vector<Route*> GenerateRoutes()
{
    pair<double, double> start(0,0);
    pair<double, double> intermediate (40,0);
    pair<double, double> end (40,-40);
    pair<double, double> end2 (80,-40);
    RouteWaypoints waypoints;
    waypoints.push_back(start);
    waypoints.push_back(intermediate);
    waypoints.push_back(end);
    waypoints.push_back(end2);

    vector<Route*> routes;

    routes.push_back(new Route("Test", waypoints));

    return routes;
}


bool simulation::SimulateGame(Game& simmedGame) 
{



    vector<Route*> routes = GenerateRoutes();
	//Generate one play
	Play firstEverPlay;

	GeneratePlay(firstEverPlay, routes);

	simmedGame.push_back(firstEverPlay);

	return true;
}