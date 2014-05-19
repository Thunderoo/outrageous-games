typedef std::pair<double, double> PlayerLocation; 

enum Position {WR, CB, FS, SS, QB};

class Player 
{
public:
	Player(PlayerLocation startingLoc, Position pos, int id) :
		m_id(id),
		m_location(startingLoc),
		m_position(pos)
	{
	}


	void UpdatePlayerLocation(PlayerLocation loc) {m_location = loc;}

private:

	int m_id;
	PlayerLocation m_location;
	Position m_position;
	double m_velocity;
	double m_direction;
};