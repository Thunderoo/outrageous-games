#include <vector>
#include "PlayState.h"

typedef std::pair<double, double> PlayerLocation; 

struct PlayerSnapshot
{
	PlayerSnapshot(int id, PlayerLocation location, bool fBall, double rot) :
		loc(location),
		PlayerID(id),
		fHasBall(fBall),
        rotation(rot)
	{
	}

	int PlayerID;
	PlayerLocation loc;
	bool fHasBall;
    double rotation;
};


class Frame 
{
public:
	Frame(const PlayState& state)
		:
	m_id(0)
	{
		for(std::vector<BasePlayer*>::const_iterator itPlayer = state.BeginPlayers(); itPlayer != state.EndPlayers(); itPlayer++)
		{
            PlayerSnapshot snapshot((*itPlayer)->GetId(), (*itPlayer)->GetLocation(), (*itPlayer)->HasBall(), (*itPlayer)->GetRotation());
			m_playerList.push_back(snapshot);
		}
	}

	void AddSnapshot(PlayerSnapshot snapshot) {m_playerList.push_back(snapshot);}

	std::vector<PlayerSnapshot>::iterator BeginPlayers() {return m_playerList.begin();}
	std::vector<PlayerSnapshot>::iterator EndPlayers() {return m_playerList.end();}

private:

	int m_id;
	std::vector<PlayerSnapshot> m_playerList;
};