/* 
 * File:   VehicleExitEvent.cc
 * Author: ehein6
 * 
 * Created on January 26, 2015, 3:43 PM
 */

#include "VehicleExitEvent.hh"
#include "../Log.hh"
#include "../StatTracker.hh"
#include "../EventQueue.hh"

VehicleExitEvent::VehicleExitEvent(Tick when, OutputZone &z)
: Event(when),
  zone(z){
}

void VehicleExitEvent::process()
{
    LOG("At time %" PRIu64 ": ", when);
    
    if (!zone.isEmpty())
    {
        Vehicle *v = zone.removeFront();
        // Compute how long the vehicle was in the system
        float travelTime = ticksToSeconds(eventQueue.Now() - v->whenArrived);
        statTracker.recordTravelTime(travelTime, v->sourceZone, v->destinationZone);
        
        LOG("Vehicle %i exits at zone %i\n", v->id, zone.getId());
        delete v;
    }
}

std::string
VehicleExitEvent::toString()
{
    std::ostringstream oss;
    oss << when << ": ";
    oss << "Vehicle exits at zone " << zone.getId();
    return oss.str();
}