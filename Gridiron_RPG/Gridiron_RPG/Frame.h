#include <vector>

typedef std::pair<double, double> PlayerLocation; 

struct PlayerSnapshot
{
	PlayerSnapshot(int id, PlayerLocation location) :
		loc(location),
		PlayerID(id)
	{
	}

	int PlayerID;
	PlayerLocation loc;
};


class Frame 
{
public:
	Frame()
		:
	m_id(0)
	{
	}

	void AddSnapshot(PlayerSnapshot snapshot) {m_playerList.push_back(snapshot);}

private:

	int m_id;
	std::vector<PlayerSnapshot> m_playerList;
};