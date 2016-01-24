/* 
 * File:   VehicleExitEvent.hh
 * Author: ehein6
 *
 * Created on January 26, 2015, 3:43 PM
 */

#ifndef VEHICLEEXITEVENT_HH
#define	VEHICLEEXITEVENT_HH

#include "Event.hh"
#include "../State/OutputZone.hh"
/**
 * Causes a vehicle the leave the simulation at one of the output zones
 */
class VehicleExitEvent : public Event {
public:
    VehicleExitEvent(Tick when, OutputZone &z);
    virtual void process();
    virtual std::string toString();
private:
    /**
     * The zone that this vehicle will exit from
     */
    OutputZone &zone;
};

#endif	

