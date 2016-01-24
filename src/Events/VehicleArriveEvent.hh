/* 
 * File:   VehicleArriveEvent.hh
 * Author: ehein6
 *
 * Created on January 26, 2015, 3:43 PM
 */

#ifndef VEHICLEARRIVEEVENT_HH
#define	VEHICLEARRIVEEVENT_HH

#include "Event.hh"
#include "../State/InputZone.hh"
/**
 * Handles the arrival of a vehicle at one of the entry zones
 */
class VehicleArriveEvent : public Event {
public:
    VehicleArriveEvent(Tick when, InputZone &z);
    virtual void process();
    virtual std::string toString();
private:
    /**
     * The zone that this vehicle will arrive in
     */
    InputZone &zone;
};

#endif	/* VEHICLEARRIVEEVENT_HH */

