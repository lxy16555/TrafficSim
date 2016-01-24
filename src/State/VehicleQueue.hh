/*
 * File:   VehicleQueue.hh
 * Author: ehein6
 *
 * Created on January 28, 2015, 5:22 PM
 */

#ifndef VEHICLEQUEUE_HH
#define	VEHICLEQUEUE_HH

#include <assert.h>
#include <deque>
#include "Vehicle.hh"

/**
 * Represents a line of cars in a single lane waiting to go through an intersection
 */
class VehicleQueue
{
private:
    /**
     * List of cars in the queue
     */
    std::deque<Vehicle*> vehicles;
    /**
     * Maximum number of vehicles
     */
    int maxSize;
public:
    /**
     * Creates a line of cars
     * @param maxSize maximum number of cars in the line
     */
    VehicleQueue(int maxSize);
    /**
     * Is the queue filled to capacity?
     * @return
     */
    bool isFull() const;
    /**
     * Is the queue empty?
     * @return
     */
    bool isEmpty() const;
    /**
     * Add a vehicle to the back of the queue
     * @param v
     */
    void insert(Vehicle *v);

    /**
     * Remove a vehicle from the front of the queue
     * @return pointer to the removed vehicle
     */
    Vehicle * removeFront();
    /**
     * How many vehicles are in this queue?
     * @return
     */
    int getSize() const;
    /**
     * Returns the vehicle at the front of the line, but does not remove it from the queue
     */
    const Vehicle * front() const;

};

#endif	/* VEHICLEQUEUE_HH */

