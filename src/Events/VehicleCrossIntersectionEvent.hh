/* 
 * File:   VehicleCrossIntersectionEvent.hh
 * Author: ehein6
 *
 * Created on January 30, 2015, 2:17 AM
 */

#ifndef VEHICLECROSSINTERSECTIONEVENT_HH
#define	VEHICLECROSSINTERSECTIONEVENT_HH

#include "Event.hh"
#include "../State/Lane.hh"
/**
 * Causes a vehicle to cross an intersection, leaving one lane and entering the next
 */
class VehicleCrossIntersectionEvent : public Event {
public:
    VehicleCrossIntersectionEvent(Tick when, Lane &src, Lane &dst);
    virtual void process();
    virtual std::string toString();
private:
    /**
     * The lane where the car comes from
     */
    Lane &srcLane;
    /**
     * The lane where the car is going
     */
    Lane &destLane;
};

#endif	/* VEHICLECROSSINTERSECTIONEVENT_HH */

