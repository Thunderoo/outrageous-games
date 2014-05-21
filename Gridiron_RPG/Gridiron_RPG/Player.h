#pragma once

#include <math.h>
#include "Route.h"
#include "Rotation.h"

typedef std::pair<double, double> PlayerLocation; 

static PlayerLocation operator+(const PlayerLocation& loc1, const PlayerLocation& loc2) 
{
    return PlayerLocation(loc1.first + loc2.first, loc1.second + loc2.second);
}

static bool ApproxEqual(const PlayerLocation& loc1, const PlayerLocation& loc2, const double dblEpsilon = 0.5)
{
    return (fabs(loc1.first - loc2.first) < dblEpsilon) && (fabs(loc1.second - loc2.second) < dblEpsilon);
}

static bool DoublesEqual(const double& dbl1, const double& dbl2, const double dblEpsilon = 0.00001) {return fabs(dbl1 - dbl2) < dblEpsilon ;}

enum Position {WR, CB, FS, SS, QB};

class BasePlayer 
{
protected:

	int m_id;
	PlayerLocation m_startLocation;
	PlayerLocation m_currentLocation;
	double m_velocity; //Feet per second. A 5 second 40 yard dash averages 24 feet per second.
	Rotation m_direction; //Degrees based on the usual cartesian definition; 0 horizontal right, 90 vertical up, 180 horizontal left, 270 vertical down
	bool m_fHasBall;

    double m_maxSpeed;
    double m_acceleration;
    double m_turnSpeed;

public:
	BasePlayer(PlayerLocation startingLoc, int id) :
		m_id(id),
		m_currentLocation(startingLoc),
        m_startLocation(startingLoc),
		m_fHasBall(false),
        m_velocity(0),
        m_direction(Rotation(0)),
        m_maxSpeed(40),
        m_acceleration(20),
        m_turnSpeed(360)
	{
	}


	void UpdatePlayerLocation(PlayerLocation loc) {m_currentLocation = loc;}

	void GiveBall() {m_fHasBall = true;}
	void TakeAwayBall() {m_fHasBall = false;}
	bool HasBall() {return m_fHasBall;}

	int GetId() const {return m_id;}
	PlayerLocation GetLocation() const {return m_currentLocation;}
    Rotation GetRotation() const {return m_direction;}

	void UpdateLocation(PlayerLocation loc) {m_currentLocation.first = loc.first; m_currentLocation.second = loc.second;}

    virtual bool UpdatePlayer() =0;
};

enum WideRecieverState{LINEDUP, 
    RUNNING_ROUTE, CATCHING_BALL, RUNNING_WITH_BALL,
    RUN_BLOCKING, PURSUING_BALL_CARRIER};

class WideReceiver : public BasePlayer
{
public:
    WideReceiver(PlayerLocation startingLoc, int id) :
      BasePlayer(startingLoc, id),
      m_AssignedRoute(NULL),
      m_currentState(LINEDUP){}

    void AssignRoute(Route* rte) {m_AssignedRoute = rte; m_currentWaypointGoal = m_AssignedRoute->FirstWaypoint();}
    WideRecieverState CurrentState() {return m_currentState;}
    void SetState(WideRecieverState newState) {m_currentState = newState;}

    //Returns true if the player moves
    bool MovePlayerOneTickAlongRoute();

    bool UpdatePlayer();

private:

    Route* m_AssignedRoute;
    RouteWaypoints::iterator m_currentWaypointGoal;
    WideRecieverState m_currentState;
};

enum QuarterbackState{UNDER_CENTRE, 
    DROPPING_BACK, PASSING, POST_PASSING};

class Quarterback : public BasePlayer
{
public:
    Quarterback(PlayerLocation startLoc, int id) :
      BasePlayer(startLoc, id),
      m_currentState(UNDER_CENTRE)
      {}

    bool UpdatePlayer();
    QuarterbackState CurrentState() {return m_currentState;}
    void SetState(QuarterbackState newState) {m_currentState = newState;}

private:
    QuarterbackState m_currentState;
};