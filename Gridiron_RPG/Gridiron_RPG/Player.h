#pragma once

#include <math.h>
#include "Route.h"

static double g_Pi = 3.14159265;

typedef std::pair<double, double> PlayerLocation; 

static PlayerLocation operator+(const PlayerLocation& loc1, const PlayerLocation& loc2) 
{
    return PlayerLocation(loc1.first + loc2.first, loc1.second + loc2.second);
}

static bool ApproxEqual(const PlayerLocation& loc1, const PlayerLocation& loc2, const double dblEpsilon = 0.01)
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
	double m_direction; //Degrees based on the usual cartesian definition; 0 horizontal right, 90 vertical up, 180 horizontal left, 270 vertical down
	bool m_fHasBall;

public:
	BasePlayer(PlayerLocation startingLoc, int id) :
		m_id(id),
		m_currentLocation(startingLoc),
        m_startLocation(startingLoc),
		m_fHasBall(false),
        m_velocity(0),
        m_direction(0)
	{
	}


	void UpdatePlayerLocation(PlayerLocation loc) {m_currentLocation = loc;}

	void GiveBall() {m_fHasBall = true;}
	void TakeAwayBall() {m_fHasBall = false;}
	bool HasBall() {return m_fHasBall;}

	int GetId() const {return m_id;}
	PlayerLocation GetLocation() const {return m_currentLocation;}
    double GetRotation() const {return m_direction;}

	void UpdateLocation(PlayerLocation loc) {m_currentLocation.first = loc.first; m_currentLocation.second = loc.second;}

    virtual bool UpdatePlayer() =0;
};

enum WideRecieverState{LINEDUP, 
    RUNNINGROUTE, RUNNINGWITHBALL,
    RUNBLOCKING, PURSUINGBALLCARRIER};

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