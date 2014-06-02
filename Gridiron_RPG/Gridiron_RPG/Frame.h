#include <vector>
#include "PlayState.h"

struct BallSnapshot
{
    BallSnapshot()
    {
        loc = Location(0,0);
        rotation = 0;
    }

    BallSnapshot(Location location, double rot) :
        loc(location),
        rotation(rot)
    {
    }

    Location loc;
    double rotation;    
};

struct PlayerSnapshot
{
	PlayerSnapshot(int id, Location location, bool fBall, double rot) :
		loc(location),
		PlayerID(id),
		fHasBall(fBall),
        rotation(rot)
	{
	}

	int PlayerID;
	Location loc;
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
        bool fBallFree = true;
		for(std::vector<BasePlayer*>::const_iterator itPlayer = state.BeginPlayers(); itPlayer != state.EndPlayers(); itPlayer++)
		{
			PlayerSnapshot snapshot((*itPlayer)->GetId(), (*itPlayer)->GetLocation(), (*itPlayer)->HasBall(), (*itPlayer)->GetRotation().GetValue());
			m_playerList.push_back(snapshot);
            if ((*itPlayer)->HasBall())
                fBallFree = false;
		}
        if (fBallFree)
            m_ballSnapshot = BallSnapshot(state.ConstGetBall().GetLocation(), state.ConstGetBall().GetRotation());
	}

	void AddSnapshot(PlayerSnapshot snapshot) {m_playerList.push_back(snapshot);}

	std::vector<PlayerSnapshot>::iterator BeginPlayers() {return m_playerList.begin();}
	std::vector<PlayerSnapshot>::iterator EndPlayers() {return m_playerList.end();}

    BallSnapshot GetBall() {return m_ballSnapshot;}

private:

	int m_id;
	std::vector<PlayerSnapshot> m_playerList;
    BallSnapshot m_ballSnapshot;
};