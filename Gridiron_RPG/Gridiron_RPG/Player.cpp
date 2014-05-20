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

void DetermineNewDirection(Rotation& currentRotation, const Rotation& requiredDirection, double turnSpeed) 
{
	if (requiredDirection > currentRotation)
	{
		Rotation newRotation(currentRotation.GetValue() + turnSpeed/60*g_Pi/180);
		currentRotation = newRotation > requiredDirection ? requiredDirection : newRotation;
	}
    else 
    {
		Rotation newRotation(currentRotation.GetValue() - turnSpeed/60*g_Pi/180);
		currentRotation = requiredDirection > newRotation ? requiredDirection : newRotation;
	}
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


	Rotation expectedDirection(CalculateExpectedDirection(targetLocation.first - m_currentLocation.first, targetLocation.second - m_currentLocation.second));

	if (!m_AssignedRoute->RouteHasHook() &&  
		(expectedDirection.GetQuadrant() == SECOND 
		||
		expectedDirection.GetQuadrant() == THIRD)
		)
    {
        expectedDirection = expectedDirection.GetQuadrant() == SECOND  ? Rotation(g_Pi/2) : Rotation(3*g_Pi/2);
        m_currentWaypointGoal->first = m_currentLocation.first - m_startLocation.first;
    }

    //Can't accelerate when turning
    if (m_direction != expectedDirection)
	{
		DetermineNewDirection(m_direction, expectedDirection, m_turnSpeed);
	}
    else
        if (m_velocity < m_maxSpeed)
            m_velocity += m_acceleration/60;

    m_currentLocation.first += m_velocity/60*cos(m_direction.GetValue());
    m_currentLocation.second += m_velocity/60*sin(m_direction.GetValue());

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