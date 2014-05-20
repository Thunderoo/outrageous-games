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

PlayState* InitialisePlayState()
{
	PlayState* state = new PlayState();
	BasePlayer* pl1 = new WideReceiver(make_pair(30, 80), 1);
	BasePlayer* pl2 = new WideReceiver(make_pair(30, 140), 2);
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