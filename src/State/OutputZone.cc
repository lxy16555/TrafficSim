/*
 * File:   OutputZone.cc
 * Author: ehein6
 *
 * Created on January 29, 2015, 6:09 PM
 */

#include "OutputZone.hh"
#include "../EventQueue.hh"
#include "../Events/VehicleExitEvent.hh"

// "Dummy" light that is always green
TrafficLight OutputZone::dummyLight(-1, true);

OutputZone::OutputZone(int i, Direction dir) :
id(i),
 Lane(dir, dummyLight, dummyLight, 0) {
    waypoints.push_back(id);
}

bool
OutputZone::canInsert() {
    return true;
}

void
OutputZone::scheduleNext()
{
    // Unconditionally schedule the next event
    eventQueue.insert(
        new VehicleExitEvent(eventQueue.Now() + 1, *this)
    );
}

void
OutputZone::connectTo(Lane *other)
{
    assert(0 && "Can't connect output zone to another lane.");
}

int
OutputZone::getId() {return id;}
