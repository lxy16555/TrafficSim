/*
 * File:   InputZone.hh
 * Author: ehein6
 *
 * Created on January 29, 2015, 6:09 PM
 */

#ifndef INPUTZONE_HH
#define	INPUTZONE_HH

#include <map>
#include "../RandomVar.hh"
#include "Lane.hh"
/**
 * Special lane where vehicles enter the system
 */
class InputZone : public Lane {
private:
    /**
     * Zone ID
     */ 
    int id;
    /**
     * Determines the rate at which cars enter from this zone
     */
    double lambda;

    /**
     * Logs inter-arrival times for analysis
     */
    FILE * debugFile;

public:
    /**
     * Is there an arrival event scheduled for this lane?
     */
    bool isArriveEventScheduled;
     /**
     * Creates an input zone
     * @param id Zone ID
     * @param dir heading direction of the lane
     * @param lambda value for the exponential distribution that controls the arrival rate at this zone
     */
    InputZone(int id, Direction dir, double lambda);
    ~InputZone();
    /**
     * Schedules the next arrival event for this zone
     */
    void scheduleNext();
    /**
     * Returns the zone ID
     */
    int getId();
    /**
     * Picks a random destination from the set of zones reachable from this zone, according to the table of probabilities
     */
    int pickRandomDest();
    /**
     * Print out the list of zones reachable from this zone
     */
    void debugRoutes();
    /**
     * Enables the creation of an output file that lists all the inter-arrival times at this input zone
     */
    void enableDebug();
    /**
     * "Dummy" light that is always green to allow vehicles to leave the input zone
     */
    static TrafficLight dummyLight;
    /**
     * Loads the list of routing probabilities 
     */
    static void initRoutingProbabilities();
    /**
     * Stores the routing probabilities (i.e. routingProbabilities[A][B] is the chance that a vehicle arriving at zone A will be routed to zone B
     */
    static std::map<int, std::map<int, float> > routingProbabilities;
};

#endif	/* INPUTZONE_HH */

