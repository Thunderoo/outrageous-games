#pragma once
#include <algorithm>

typedef std::pair<double, double> Location; 

class Ball
{
public:
    Ball(Location location, double velocity, double direction) :
        m_location(location),
        m_velocity(velocity),
        m_direction(direction){}

    void IncrementLocation() {m_location.first += m_velocity/60*cos(m_direction); m_location.second += m_velocity/60*sin(m_direction);}

    Location GetLocation() {return m_location;}
    double GetRotation() {return m_direction;}

    void UpdateLocation(Location loc) {m_location = loc;}
    void UpdateVelocity(double v) {m_velocity = v;}
    void UpdateDirection(double d) {m_direction = d;}
private:
    Location m_location;
    double m_velocity;
    double m_direction;
};