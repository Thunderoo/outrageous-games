#pragma once
#include "Player.h"

enum PlayType{RUN, PASS, SPECIAL_TEAMS};

class PlayDetails
{

public:

	PlayDetails(PlayType type, Location qbDropBackPoint)
	{
	}

private:


	Location m_qbDropBackPoint;
	PlayType m_playType;
}