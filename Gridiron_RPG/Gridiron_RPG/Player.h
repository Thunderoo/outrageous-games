#pragma once

#include <math.h>
#include "Route.h"
#include "Rotation.h"
#include "Ball.h"

typedef std::pair<double, double> Location; 

static Location operator+(const Location& loc1, const Location& loc2) 
{
    return Location(loc1.first + loc2.first, loc1.second + loc2.second);
}

static bool ApproxEqual(const Location& loc1, const Location& loc2, const double dblEpsilon = 0.5)
{
    return (fabs(loc1.first - loc2.first) < dblEpsilon) && (fabs(loc1.second - loc2.second) < dblEpsilon);
}

static bool DoublesEqual(const double& dbl1, const double& dbl2, const double dblEpsilon = 0.00001) {return fabs(dbl1 - dbl2) < dblEpsilon ;}

enum Position {WR, CB, FS, SS, QB};

class BasePlayer 
{
protected:

	int m_id;
	Location m_startLocation;
	Location m_currentLocation;
	double m_velocity; //Feet per second. A 5 second 40 yard dash averages 24 feet per second.
	Rotation m_direction; //Degrees based on the usual cartesian definition; 0 horizontal right, 90 vertical up, 180 horizontal left, 270 vertical down
	bool m_fHasBall;

    double m_maxSpeed;
    double m_acceleration;
    double m_turnSpeed;

public:
	BasePlayer(Location startingLoc, int id) :
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



	void GiveBall() {m_fHasBall = true;}
	void TakeAwayBall() {m_fHasBall = false;}
	bool HasBall() {return m_fHasBall;}

	int GetId() const {return m_id;}
	Location GetLocation() const {return m_currentLocation;}
    Rotation GetRotation() const {return m_direction;}
    double GetVelocity() const {return m_velocity;}


    virtual bool UpdatePlayer(Ball& ball) =0;
};

enum WideRecieverState{LINEDUP, 
    RUNNING_ROUTE, RUNNING_ROUTE_LOOKING_FOR_BALL, GETTING_OPEN, CATCHING_BALL, RUNNING_WITH_BALL,
    RUN_BLOCKING, PURSUING_BALL_CARRIER};

class WideReceiver : public BasePlayer
{
public:
    WideReceiver(Location startingLoc, int id) :
      BasePlayer(startingLoc, id),
      m_AssignedRoute(NULL),
      m_currentState(LINEDUP){}

    void AssignRoute(Route* rte) {m_AssignedRoute = rte; m_currentWaypointGoal = m_AssignedRoute->FirstWaypoint();}
    WideRecieverState CurrentState() {return m_currentState;}
    void SetState(WideRecieverState newState) {m_currentState = newState;}
    Location GetTargetLocation() {return m_startLocation + *m_currentWaypointGoal;}


    //Returns true if the player moves
    bool MovePlayerOneTickAlongRoute();

    bool UpdatePlayer(Ball& ball);

private:

    Route* m_AssignedRoute;
    RouteWaypoints::iterator m_currentWaypointGoal;
    WideRecieverState m_currentState;
};

enum QuarterbackState{UNDER_CENTRE, 
    DROPPING_BACK, STANDING_IN_POCKET, THROWING_BALL, DO_NOTHING};

class Quarterback : public BasePlayer
{
public:
    Quarterback(Location startLoc, int id, std::vector<WideReceiver*> receivers) :
      BasePlayer(startLoc, id),
      m_currentState(UNDER_CENTRE),
      m_maxDropBackSpeed(20),
      m_rgReceivers(receivers),
      m_passVelocity(100)
    {
        m_dropBackSpot = Location(startLoc.first - 10, startLoc.second);
        m_throwTarget = Location(-200, -200);
    }

    bool UpdatePlayer(Ball& ball);
    QuarterbackState CurrentState() {return m_currentState;}
    void SetState(QuarterbackState newState) {m_currentState = newState;}

private:

    bool WrOpenForThrow(WideReceiver* wr);
    Location WhereToThrow(WideReceiver* wr, double& time);


    Location m_throwTarget;
    Location m_dropBackSpot;
    QuarterbackState m_currentState;
    double m_maxDropBackSpeed;
    std::vector<WideReceiver*> m_rgReceivers;

    int m_passWindup;
    double m_passVelocity;

    Location m_locThrowingLocation;
};