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

    if (!DoublesEqual(m_direction, expectedDirectionDegrees)) 
        m_direction = expectedDirectionDegrees;

    if (m_velocity == 0)
        m_velocity = 24;

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
        SetState(WideRecieverState::RUNNINGROUTE);

    if (wrState == RUNNINGROUTE)
	    if (MovePlayerOneTickAlongRoute())
            playFinished = true;

	return playFinished;
}