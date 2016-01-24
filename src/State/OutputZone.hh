/*
 * File:   OutputZone.hh
 * Author: ehein6
 *
 * Created on January 29, 2015, 6:09 PM
 */

#ifndef OUTPUTZONE_HH
#define	OUTPUTZONE_HH

#include "../RandomVar.hh"
#include "Lane.hh"
#include "TrafficLight.hh"
/**
 * Special lane where vehicles exit the system
 */
class OutputZone : public Lane{
private:
    /**
     * Zone ID
     */ 
    int id;
public:
    /**
     * Constructs an output zone
     */
    OutputZone(int id, Direction dir);
    /**
     * Is there room for another car in the lane? (always true)
     */
    bool canInsert();
    /**
     * Schedules the next exit event from this zone
     */
    void scheduleNext();
    /**
     * Returns the zone ID
     */ 
    int getId();
    
    void connectTo(Lane *other);
    static TrafficLight dummyLight;
};

#endif

