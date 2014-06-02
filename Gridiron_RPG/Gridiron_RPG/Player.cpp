#include "Player.h"
#include <cmath>

using namespace std;

double CalculateExpectedDirection(double x, double y)
{
    if (x == 0 && y > 0)
        return g_Pi/2;
    
    if (x == 0 && y < 0)
        return -g_Pi/2;
    
    double directionRadians = atan2(y, x);

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
    Location targetLocation = m_startLocation + *m_currentWaypointGoal;

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

bool WideReceiver::UpdatePlayer(Ball& ball) 
{
    bool playFinished = false;
	//Current location and state
	Location loc = GetLocation();
    WideRecieverState wrState = CurrentState();

    if (wrState == LINEDUP)
        SetState(RUNNING_ROUTE);

    if (wrState == RUNNING_ROUTE)
    {
	    if (MovePlayerOneTickAlongRoute()) 
        {
            SetState(GETTING_OPEN);
            playFinished = true;
        }
        if (ApproxEqual(loc, ball.GetLocation()))
        {
            GiveBall();
            SetState(RUNNING_WITH_BALL);
            playFinished = true;
        }
    }
    if (wrState == RUNNING_ROUTE_LOOKING_FOR_BALL)
    {
        if (ApproxEqual(loc, ball.GetLocation()))
        {
            GiveBall();
            SetState(RUNNING_WITH_BALL);
            playFinished = true;
        }
        else
            MovePlayerOneTickAlongRoute();
    }
	return playFinished;
}

bool Quarterback::WrOpenForThrow(WideReceiver* wr)
{
    if (wr->GetRotation().GetQuadrant() == FOURTH)
        return true;
    return false;
}

Location Quarterback::WhereToThrow(WideReceiver* wr, double& time) 
{
    double v1 = wr->GetVelocity();
    double v2 = m_passVelocity;
    Location targetLocation = wr->GetTargetLocation();
    Location currentLocation = wr->GetLocation();
    double theta = CalculateExpectedDirection(targetLocation.first - currentLocation.first, targetLocation.second - currentLocation.second);
    double x1_minus_x2 = currentLocation.first - m_currentLocation.first;
    double y1_minus_y2 = currentLocation.second - m_currentLocation.second;

    double a = pow(v1,2) - pow(v2, 2);
    double b = 2*x1_minus_x2*v1*cos(theta) + 2*y1_minus_y2*v1*sin(theta);
    double c = pow(x1_minus_x2, 2) + pow(y1_minus_y2, 2);

    time = max((-b - sqrt(pow(b,2) - 4*a*c))/(2*a), (-b + sqrt(pow(b,2) - 4*a*c))/(2*a));

    double pass_Distance = time*v2;
    return Location(currentLocation.first + v1*time*cos(theta), currentLocation.second + v1*time*sin(theta));

}

bool Quarterback::UpdatePlayer(Ball& ball)
{
    bool playFinished = false;

    Location loc = GetLocation();
    QuarterbackState qbState = CurrentState();

    if (qbState == UNDER_CENTRE)
    {
        GiveBall();
        SetState(DROPPING_BACK);
        return playFinished;
    }
    
    if (qbState == DROPPING_BACK)
    {
        if (ApproxEqual(m_dropBackSpot, m_currentLocation))
            SetState(STANDING_IN_POCKET);
        if (m_velocity < m_maxDropBackSpeed)
            m_velocity += m_acceleration/60;
        m_currentLocation.first -= m_velocity/60;
    }

    if (qbState == DROPPING_BACK || qbState == STANDING_IN_POCKET)
    {
        for(vector<WideReceiver*>::iterator itWr = m_rgReceivers.begin(); itWr != m_rgReceivers.end(); itWr++)
        {
            WideReceiver* target = *itWr;
            if (WrOpenForThrow(target))
            {
                double time;
                m_throwTarget = WhereToThrow(target, time);
                SetState(THROWING_BALL);
                TakeAwayBall();
                ball.UpdateVelocity(m_passVelocity);
                ball.UpdateDirection(CalculateExpectedDirection(m_throwTarget.first - m_currentLocation.first, m_throwTarget.second - m_currentLocation.second));
                Location test = Location(m_currentLocation.first + m_passVelocity*time*cos(ball.GetRotation()), m_currentLocation.second + m_passVelocity*time*sin(ball.GetRotation()));
                int i = 1;
            }
        }
    }
    if (qbState == THROWING_BALL)
    {
        if (ApproxEqual(m_throwTarget, ball.GetLocation(), 1))
            playFinished = true;
    }

    return playFinished;
}