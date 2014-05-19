#include "SimulationEngine.h"
#include "Player.h"
#include "PlayState.h"
#include <vector>

using namespace std;
using namespace simulation;

		
bool UpdatePlayer(Player& player)
{
	//Continue route
	PlayerLocation loc = player.GetLocation();
	loc.first += 0.4;

	player.UpdateLocation(loc);

	if (loc.first >= 150)
		return true;
	return false;
}

bool IncrementPlay(PlayState* state) 
{
	bool fPlayIsOver = false;
	for(vector<Player*>::iterator itPlayer = state->BeginPlayers(); itPlayer != state->EndPlayers(); itPlayer++)
	{
		if (UpdatePlayer(*(*itPlayer)))
			fPlayIsOver = true;
	}
	return fPlayIsOver;
}

PlayState* InitialisePlayState()
{
	PlayState* state = new PlayState();
	Player* pl1 = new Player(make_pair(30, 80), Position::WR, 1);
	Player* pl2 = new Player(make_pair(30, 140), Position::WR, 2);
	pl1->GiveBall();
	state->AddPlayer(pl1);
	state->AddPlayer(pl2);

	return state;
}

void GeneratePlay(Play& generatedPlay)
{
	bool fPlayOver = false;
	PlayState* currentState = InitialisePlayState();
	Frame* frame = new Frame(*currentState);
	generatedPlay.push_back(frame);

	while (!fPlayOver) {
		fPlayOver = IncrementPlay(currentState);
		Frame* frame = new Frame(*currentState);
		generatedPlay.push_back(frame);
	}
}


bool simulation::SimulateGame(Game& simmedGame) 
{
	//Generate one play
	Play firstEverPlay;

	GeneratePlay(firstEverPlay);

	simmedGame.push_back(firstEverPlay);

	return true;
}