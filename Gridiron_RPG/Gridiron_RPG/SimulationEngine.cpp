#include "SimulationEngine.h"
#include "Player.h"
#include <vector>

using namespace std;
using namespace simulation;

Frame GenerateNextFrame(Frame& frame)
{
	Frame newFrame;


	return newFrame;
}

void InitialiseFirstFrame(Frame& frame)
{

}

void GeneratePlay(Play& generatedPlay)
{
	bool fPlayOver = false;

	Frame currentFrame;

	InitialiseFirstFrame(currentFrame);

	generatedPlay.push_back(currentFrame);

	while (!fPlayOver) {
		Frame newFrame = GenerateNextFrame(currentFrame);
		generatedPlay.push_back(newFrame);
		currentFrame = newFrame;

		fPlayOver = true;
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