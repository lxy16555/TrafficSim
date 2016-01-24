/*
 * File:   Lane.cc
 * Author: ehein6
 *
 * Created on January 29, 2015, 4:02 PM
 */

#include <algorithm>

#include "Lane.hh"
#include "../EventQueue.hh"
#include "../Events/VehicleCrossIntersectionEvent.hh"
#include "../Log.hh"
#include "OutputZone.hh"

Lane::Lane(Direction d, TrafficLight &t, TrafficLight &l, double lanelength) :
  through(t),
  left(l),
  line(10),
  direct(d),
  isCrossingEventScheduled(false),
  lanelength(lanelength)
{
	if (lanelength) {
		line = (int)(lanelength/(CarLength + DisBetween));
	}
    //LOG("Created lane, governed by traffic light %i\n",light.getId());
}

void
Lane::connectTo(Lane *other)
{
    destinations.push_back(other);
}

// Get the direction that is a left turn from the input
Direction leftOf(Direction d)
{
    switch (d)
    {
        case NORTH: return WEST;
        case SOUTH: return EAST;
        case EAST:  return NORTH;
        case WEST:  return SOUTH;
    }
}

// Get the direction that is opposite from the input
Direction oppositeOf(Direction d)
{
    switch (d)
    {
        case NORTH: return SOUTH;
        case SOUTH: return NORTH;
        case EAST:  return WEST;
        case WEST:  return EAST;
    }
}

// Get the direction that is a right turn from the input
Direction rightOf(Direction d)
{
    return oppositeOf(leftOf(d));
}

void
Lane::scheduleNext()
{
    // Don't schedule a crossing if there are no cars in line
    if (line.isEmpty()) { return; }
    // Don't re-schedule the event
    if (isCrossingEventScheduled) { return; }

    //LOG("in Lane::scheduleNext(): light %i is %s\n",
    //    light.getId(),
    //    TrafficLight::colorToString(light.getColor()).c_str());

    Tick when;
    // TODO replace with actual time to cross intersection
    Tick crossingTime = secondsToTicks(2.9);
    // TODO replace with actual driver delay time
    Tick driverDelay = secondsToTicks(1.2);

    // Use the waypoint routing to find the destination lane
    Lane *destLane = routeTo(line.front()->destinationZone);
    float temp;
    if (this->lanelength)
    	temp = 1;//(float)((this->lanelength - this->line.getSize() * (CarLength + DisBetween)) / AvgVelocity);
    else
    	temp = 1;
    Tick TimeOnRoad = secondsToTicks(temp);

    TrafficLight *myLight;
    // Pick the light to look at based on the relative direction of the destination lane
    if (destLane->direct == this->direct
    ||  destLane->direct == rightOf(this->direct))
    {
        myLight = &through;
    }
    else if (destLane->direct == leftOf(this->direct) || destLane->direct == oppositeOf(this->direct))
    {
        myLight = &left;
    }
    // Make sure we didn't get a dummy red light
    assert(myLight->getId() != -2);

    switch (myLight->getColor())
    {
        case TrafficLight::RED:
        {
            // Wait for light to turn green
            when = myLight->getNextGreen() + driverDelay + crossingTime + TimeOnRoad;
            break;
        }
        case TrafficLight::YELLOW:
        {
            // Check to see if there is enough time to cross before red
            if (eventQueue.Now() + crossingTime <= myLight->getNextGreen())
            {
            	when = eventQueue.Now() + TimeOnRoad + crossingTime;
            } else {
            	when = myLight->getNextGreen() + driverDelay + crossingTime + TimeOnRoad;
            }
            break;
        }
        case TrafficLight::GREEN:
        {
            // Wait for vehicle to cross intersection
            if (eventQueue.Now() + crossingTime <= myLight->getNextRed())
                    when = eventQueue.Now() + TimeOnRoad + crossingTime;
            else
                    when = eventQueue.Now() + myLight->getNextGreen() + crossingTime;
            break;
        }
    }

    //LOG("Scheduled crossing for tick %" PRIu64 "\n", when);
    // TODO route vehicle to correct lane based on destination
    // TODO Calculate arrival at destlane based on velocity, accel, number of cars in lane, etc.
    eventQueue.insert(
        new VehicleCrossIntersectionEvent(when, *this, *destLane)
    );
    isCrossingEventScheduled = true;

}

std::vector<int>
Lane::_calcWaypoints(Lane *src)
{
    std::vector<int> r;
    for (Lane *lane : src->destinations)
    {
        // If any lanes are output zones, append their ID's to the list
        if (OutputZone *z = dynamic_cast <OutputZone*> (lane))
        {
            r.push_back(z->getId());
        }
        // Recursively search all children of the lane
        std::vector<int> rs = _calcWaypoints(lane);
        r.insert(r.end(), rs.begin(), rs.end());
    }
    return r;
}

void
Lane::calcWaypoints()
{
    waypoints = _calcWaypoints(this);
    // Sort and remove duplicates
    std::sort( waypoints.begin(), waypoints.end() );
    waypoints.erase( std::unique( waypoints.begin(), waypoints.end() ), waypoints.end() );
}

Lane *
Lane::routeTo(int dest)
{
	Lane *destlane = NULL;
    // Check all of our destinations for the one that leads to the exit
    for (Lane *lane : destinations)
    {
        for (int w : lane->waypoints)
        {
            if (w == dest) {
            	if (!destlane || destlane->line.getSize() >= lane->line.getSize())
            		destlane = lane;
            }
        }
    }
    return destlane;

    LOG("Error: No route from this lane to zone %i\n", dest);
    assert(0);
}

void
Lane::debugRoutes()
{
    LOG("Lane can reach: ");
    for (int w : waypoints)
    {
        LOG("%i, ", w);
    }
    LOG("\n");
}

bool
Lane::canInsert()
{
    return !line.isFull();
}

bool
Lane::isEmpty()
{
    return line.isEmpty();
}

void
Lane::insert(Vehicle *v)
{
    line.insert(v);
    scheduleNext();
}

Vehicle*
Lane::removeFront(){
    return line.removeFront();
}

