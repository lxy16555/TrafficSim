/*
 * File:   Lane.hh
 * Author: ehein6
 *
 * Created on January 29, 2015, 4:02 PM
 */

#ifndef LANE_HH
#define	LANE_HH

#include <vector>
#include "VehicleQueue.hh"
#include "TrafficLight.hh"
/**
 * Represents the four cardinal directions in which a lane can be directed
 */
enum Direction {NORTH, SOUTH, EAST, WEST};
/**
 * Represents a traffic lane.
 * The key components of a lane are the line of cars, a set of traffic lights, and routing info about which lanes are connected to this one
 */
class Lane
{
protected:

    /**
     * Cars will enter this lane after they cross the intersection
     */
    std::vector<Lane*> destinations;

    /**
     * List of output zones reachable from this lane.
     * Call calcWaypoints to initialize this by recursively searching the network of lanes
     */
    std::vector<int> waypoints;

    /**
    * Recursive body of calcWaypoints()
    */
    std::vector<int> _calcWaypoints(Lane *src);

    /**
     *  Length of each car
     */
    const double CarLength = 17;
    /**
     *  Distance between cars
     */
    const double DisBetween = 2.5;
    /**
     *  Velocity of each car
     */
    const double AvgVelocity = 50;
public:
    /**
     *  Which direction is this lane heading?
     */
    Direction direct;
    /**
     *  Length of this lane
     */
    double lanelength;
    /**
     * Constructs a lane
     * @param dir which way the lane is heading
     * @param through The traffic light that controls vehicles going straight or turning right
     * @param left The traffic light that controls vehicles turning left
     * @param lanelength Length of the lane in feet.
     */
    Lane(Direction dir, TrafficLight &through, TrafficLight &left, double lanelength);

    /**
     * The traffic light that governs cars going straight or turning right from this lane
     */
    TrafficLight &through;
    /**
     * The traffic light that governs cars turning left from this lane
     */
    TrafficLight &left;

    /**
     * Line of cars waiting to cross the intersection
     */
    VehicleQueue line;
    
    /**
     * Is there a Vehicle crossing event scheduled, or is the intersection idle?
     */
    bool isCrossingEventScheduled;

    /**
     * Is there room for another car in the lane?
     */
    virtual bool canInsert();
    /**
     * Is the lane empty of cars?
     */
    virtual bool isEmpty();
    /**
     * Add a car to the back of the line
     */
    virtual void insert(Vehicle *v);
    /**
     * Grab the first car in the line
     */
    virtual Vehicle *removeFront();
    /**
     * Schedule the next intersection crossing for the first car in this lane
     */
    virtual void scheduleNext();
    /**
     * Set other as a destination of this lane
     */
    virtual void connectTo(Lane *other);

    /**
     * Pick the lane from <code>destinations</code> that leads to the specified destination zone
     * @param dest ID of the destination zone
     * @return
     */
    Lane *routeTo(int dest);

    /**
     * Calculate a list of all zones reachable from this lane
     */
    void calcWaypoints();
    /**
     * Print the list of zones reachable from this lane
     */
    virtual void debugRoutes();
};


#endif	/* LANE_HH */

