#pragma once

#include <vector>
#include "Frame.h"

namespace simulation {

	typedef std::vector<Frame> Play;
	typedef std::vector<Play> Game;

	bool SimulateGame(Game& simmedGame);
}