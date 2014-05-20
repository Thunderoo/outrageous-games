#include <cmath>
#include <assert.h>

enum Quadrant{FIRST, SECOND,THIRD, FOURTH, UNDEFINED};

static double g_Pi = 3.14159265;

class Rotation
{
public:
    Rotation(double radRotation)
    {
        while (radRotation < -g_Pi)
            radRotation += 2*g_Pi;
		while (radRotation > g_Pi)
			radRotation -= 2*g_Pi;


        assert(radRotation >= -g_Pi);
        assert(radRotation <= g_Pi);
        m_radianRotation = radRotation;

        m_quad = UNDEFINED;
        if (radRotation >= 0 && radRotation <= g_Pi/2)
            m_quad = FIRST;
        if (radRotation > g_Pi/2 && radRotation <= g_Pi)
            m_quad = SECOND;
        if (radRotation > -g_Pi && radRotation <= -g_Pi/2)
            m_quad = THIRD;
        if (radRotation > -g_Pi/2 && radRotation < 0)
            m_quad = FOURTH;
    }

    bool operator==(const Rotation& other)
    {
        return (fabs(m_radianRotation - other.m_radianRotation) < 0.00001);
    }

	bool operator!=(const Rotation& other)
	{
		return (fabs(m_radianRotation - other.m_radianRotation) > 0.00001);
	}

	bool operator>(const Rotation& other) const
	{
		return m_radianRotation > other.m_radianRotation;
	}

	Rotation operator+(const Rotation& other)
	{
		return Rotation(m_radianRotation + other.m_radianRotation);
	}

    double GetValue() const {return m_radianRotation;}
	Quadrant GetQuadrant() const {return m_quad;}

private:
    double m_radianRotation;
    Quadrant m_quad;
};