#pragma once

typedef std::pair<double, double> PlayerLocation; 

enum Position {WR, CB, FS, SS, QB};

class Player 
{
public:
	Player(PlayerLocation startingLoc, Position pos, int id) :
		m_id(id),
		m_location(startingLoc),
		m_position(pos),
		m_fHasBall(false)
	{
	}


	void UpdatePlayerLocation(PlayerLocation loc) {m_location = loc;}

	void GiveBall() {m_fHasBall = true;}
	void TakeAwayBall() {m_fHasBall = false;}
	bool HasBall() {return m_fHasBall;}

	int GetId() const {return m_id;}
	PlayerLocation GetLocation() const {return m_location;}

	void UpdateLocation(PlayerLocation loc) {m_location.first = loc.first; m_location.second = loc.second;}

private:

	int m_id;
	PlayerLocation m_location;
	Position m_position;
	double m_velocity;
	double m_direction;
	bool m_fHasBall;
};