#pragma once

#include <vector>
#include "Player.h"


class PlayState 
{
public:
	PlayState()
	{
	}

	void AddPlayer(BasePlayer* pl) {m_players.push_back(pl);}

	std::vector<BasePlayer*>::iterator BeginPlayers() {return m_players.begin();}
	std::vector<BasePlayer*>::iterator EndPlayers() {return m_players.end();}

	std::vector<BasePlayer*>::const_iterator BeginPlayers() const {return m_players.begin();}
	std::vector<BasePlayer*>::const_iterator EndPlayers() const {return m_players.end();}

private:
	std::vector<BasePlayer*> m_players;

};