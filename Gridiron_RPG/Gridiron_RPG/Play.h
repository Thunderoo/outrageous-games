#pragma once
#include "Player.h"

enum PlayType{RUN, PASS, SPECIAL_TEAMS};

class PlayDetails
{

public:

	PlayDetails(){}

private:


	PlayerLocation m_qbDropBackPoint;
	PlayType m_playType;
}