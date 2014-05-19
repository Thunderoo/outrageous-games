#include <vector>
#include "Player.h"


class PlayState 
{
	PlayState()
	{
	}

	void AddPlayer(Player* pl) {m_players.push_back(pl);}

private:
	std::vector<Player*> m_players;

};