#include "Player.h"
#include <cmath>




double CalculateExpectedDirection(double x, double y)
{
    if (x == 0 && y > 0)
        return 90.0;
    
    if (x == 0 && y < 0)
        return 270.0;
    
    double directionRadians = atan2(y, x);
    double directionDegrees = directionRadians * 180/g_Pi;

    return directionRadians;
}

bool WideReceiver::MovePlayerOneTickAlongRoute() 
{
    if (m_currentWaypointGoal == m_AssignedRoute->LastWaypoint())
            return true;

    //Calculate target location
    PlayerLocation targetLocation = m_startLocation + *m_currentWaypointGoal;

    //Is the player at the target location? If so we need the next target
    if (ApproxEqual(targetLocation, m_currentLocation) && m_currentWaypointGoal != m_AssignedRoute->LastWaypoint()) 
    {
        m_currentWaypointGoal++;
        if (m_currentWaypointGoal == m_AssignedRoute->LastWaypoint())
            return true;
        targetLocation = m_startLocation + *m_currentWaypointGoal;
    }

    double deltaX = targetLocation.first - m_currentLocation.first;
    double deltaY = targetLocation.second - m_currentLocation.second;
    double expectedDirectionRadians = CalculateExpectedDirection(deltaX, deltaY);
    double expectedDirectionDegrees = expectedDirectionRadians * 180/g_Pi;
    expectedDirectionDegrees = expectedDirectionDegrees >= 0 ? expectedDirectionDegrees : expectedDirectionDegrees + 360;

    if (!m_AssignedRoute->RouteHasHook() &&  expectedDirectionDegrees > 90 && expectedDirectionDegrees < 270)
    {
        expectedDirectionDegrees = expectedDirectionDegrees < 180 ? 90 : 270;
        m_currentWaypointGoal->first = m_currentLocation.first - m_startLocation.first;
    }

    //Can't accelerate when turning
    if (!DoublesEqual(m_direction, expectedDirectionDegrees)) 
        if (fmod(m_direction + 180, 360) > expectedDirectionDegrees)
            m_direction = m_direction + m_turnSpeed/60 > expectedDirectionDegrees ? expectedDirectionDegrees :  fmod(m_direction + m_turnSpeed/60, 360);
        else
            m_direction = 360 + fmod(m_direction - m_turnSpeed/60, 360);
    else
        if (m_velocity < m_maxSpeed)
            m_velocity += m_acceleration/60;

    m_currentLocation.first += m_velocity/60*cos(m_direction*g_Pi/180);
    m_currentLocation.second += m_velocity/60*sin(m_direction*g_Pi/180);

    return false;
}

bool WideReceiver::UpdatePlayer() 
{
    bool playFinished = false;
	//Current location and state
	PlayerLocation loc = GetLocation();
    WideRecieverState wrState = CurrentState();

    if (wrState == LINEDUP)
        SetState(WideRecieverState::RUNNING_ROUTE);

    if (wrState == RUNNING_ROUTE)
	    if (MovePlayerOneTickAlongRoute())
            playFinished = true;

	return playFinished;
}

bool Quarterback::UpdatePlayer()
{
    bool playFinished = false;

    PlayerLocation loc = GetLocation();
    QuarterbackState qbState = CurrentState();

    if (qbState == UNDER_CENTRE)
    {
        GiveBall();
        SetState(DROPPING_BACK);
        return playFinished;
    }
    
    if (qbState == DROPPING_BACK)
    {

    }

    return playFinished;
}