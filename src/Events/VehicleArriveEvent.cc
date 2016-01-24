/* 
 * File:   VehicleArriveEvent.cc
 * Author: ehein6
 * 
 * Created on January 26, 2015, 3:43 PM
 */

#include "VehicleArriveEvent.hh"
#include "../Log.hh"

VehicleArriveEvent::VehicleArriveEvent(Tick when, InputZone &z)
: Event(when),
  zone(z){
}

void VehicleArriveEvent::process()
{
    LOG("At time %" PRIu64 ": ", when);
    
    // TODO schedule arrival time at intersection based on how many cars are in the queue
    // TODO randomize destination of this car
    if (zone.canInsert())
    {
        Vehicle *v = new Vehicle(when, zone.getId(), zone.pickRandomDest());
        zone.insert(v);
        LOG("Vehicle %i arrives at zone %i\n", v->id, zone.getId());
    }
    else{
        LOG("No room to insert into zone %i\n", zone.getId());
    }
    
    zone.isArriveEventScheduled = false;
    zone.scheduleNext();
}

std::string
VehicleArriveEvent::toString()
{
    std::ostringstream oss;
    oss << when << ": ";
    oss << "Vehicle arrives at zone " << zone.getId();
    return oss.str();
}