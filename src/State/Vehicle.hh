/* 
 * File:   Vehicle.hh
 * Author: ehein6
 *
 * Created on January 28, 2015, 5:18 PM
 */

#ifndef VEHICLE_HH
#define	VEHICLE_HH

#include "../Ticks.hh"

/**
 * Represents a single vehicle in the simulation
 */
class Vehicle {
public:
    /**
     * Vehicle ID
     */
    int id;
    /**
     * Zone where this vehicle originated
     */
    int sourceZone;
    /**
     * Zone where this vehicle wants to go
     */
    int destinationZone;
    /**
     * Tick when this vehicle entered the system
     */
    Tick whenArrived;

    /**
     * Creates a vehicle
     * @param now Tick when the vehicle entered the system
     * @param src source zone
     * @param dst destination zone
     */
    Vehicle(Tick now, int src, int dst);
    /**
     * Next ID to assign to a vehicle
     */
    static int nextId;
};


#endif	/* VEHICLE_HH */

