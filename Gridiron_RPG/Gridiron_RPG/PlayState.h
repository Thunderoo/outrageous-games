#pragma once

#include <vector>
#include "Player.h"


class PlayState 
{
public:
	PlayState()
	{
	}

	void AddPlayer(Player* pl) {m_players.push_back(pl);}

	std::vector<Player*>::iterator BeginPlayers() {return m_players.begin();}
	std::vector<Player*>::iterator EndPlayers() {return m_players.end();}

	std::vector<Player*>::const_iterator BeginPlayers() const {return m_players.begin();}
	std::vector<Player*>::const_iterator EndPlayers() const {return m_players.end();}

private:
	std::vector<Player*> m_players;

};