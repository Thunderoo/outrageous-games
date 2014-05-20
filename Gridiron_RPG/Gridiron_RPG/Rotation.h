#pragma once
#include <cmath>
#include <assert.h>

enum Quadrant{FIRST, SECOND,THIRD, FOURTH, UNDEFINED};

static double g_Pi = 3.14159265;

class Rotation
{
public:
    Rotation(double radRotation)
    {
        while (radRotation <= 0)
            radRotation += 2*g_Pi;

        assert(radRotation >= 0);
        assert(radRotation <= 2*g_Pi);
        m_radianRotation = radRotation;

        m_quad = UNDEFINED;
        if (radRotation >= 0 && radRotation <= g_Pi/2)
            m_quad = FIRST;
        if (radRotation > g_Pi/2 && radRotation <= g_Pi)
            m_quad = SECOND;
        if (radRotation > g_Pi && radRotation <= 3*g_Pi/2)
            m_quad = THIRD;
        if (radRotation > 3*g_Pi/2 && radRotation <= 2*g_Pi)
            m_quad = FOURTH;
    }

    bool operator==(const Rotation& other)
    {
        return (fabs(m_radianRotation - other.GetValue()) < 0.00001);
    }

    double GetValue() const {return m_radianRotation;}

private:
    double m_radianRotation;
    Quadrant m_quad;
};