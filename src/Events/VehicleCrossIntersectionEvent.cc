/* 
 * File:   VehicleCrossIntersectionEvent.cc
 * Author: ehein6
 * 
 * Created on January 30, 2015, 2:17 AM
 */

#include "VehicleCrossIntersectionEvent.hh"
#include "../Log.hh"

VehicleCrossIntersectionEvent::VehicleCrossIntersectionEvent(Tick when, Lane &src, Lane &dst)
: Event(when), srcLane(src), destLane(dst) {    
}

void VehicleCrossIntersectionEvent::process()
{
    LOG("At time %" PRIu64 ": ", when);
    
    // Is there a car to send?
    if (srcLane.isEmpty())
    {
        LOG("Can't send a car across, no cars in the line\n");
    } else {
        // Is there room in the next lane?
        if (!destLane.canInsert())
        {
            LOG( "Can't send vehicle %i across, no room in the next lane\n", srcLane.line.front()->id);
        } else {
            Vehicle *v = srcLane.removeFront();
            destLane.insert(v);
            LOG( "Vehicle %i crosses the intersection\n", v->id);
        }
    }
    
    srcLane.isCrossingEventScheduled = false;
    srcLane.scheduleNext();
}

std::string
VehicleCrossIntersectionEvent::toString()
{
    std::ostringstream oss;
    oss << when << ": ";
    oss << "Vehicle crosses the intersection ";
    return oss.str();
}
