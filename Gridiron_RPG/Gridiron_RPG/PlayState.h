#pragma once

#include <vector>
#include "Player.h"
#include "Ball.h"

enum CurrentPlayState{PRE_SNAP, QB_DROPBACK, QB_THROWING, BALL_IN_AIR};

class PlayState 
{
public:
	PlayState()
	{
	}

	void AddPlayer(BasePlayer* pl) {m_players.push_back(pl);}
    void AddBall(Ball* bl) {m_pBall = bl;}

	std::vector<BasePlayer*>::iterator BeginPlayers() {return m_players.begin();}
	std::vector<BasePlayer*>::iterator EndPlayers() {return m_players.end();}

	std::vector<BasePlayer*>::const_iterator BeginPlayers() const {return m_players.begin();}
	std::vector<BasePlayer*>::const_iterator EndPlayers() const {return m_players.end();}

    Ball& ConstGetBall() const {return *m_pBall;}
    Ball& GetBall() {return *m_pBall;}

private:
	std::vector<BasePlayer*> m_players;
    Ball* m_pBall;

};