#include <string>
#include <vector>

typedef std::vector<std::pair<double, double> > RouteWaypoints;


class Route
{
public:
    Route(std::string name, RouteWaypoints waypoints) :
        m_routeName(name),
        m_routeWaypoints(waypoints),
        fIsComebackRoute(false){}

        RouteWaypoints::iterator FirstWaypoint() {return m_routeWaypoints.begin();}
        RouteWaypoints::iterator LastWaypoint() {return m_routeWaypoints.end();}

        bool RouteHasHook() {return fIsComebackRoute;}

private:

    std::string m_routeName;
    RouteWaypoints m_routeWaypoints;
    bool fIsComebackRoute;
};