/*
 * File:   Intersection.hh
 * Author: ehein6
 *
 * Created on January 29, 2015, 4:03 PM
 */

#ifndef INTERSECTION_HH
#define	INTERSECTION_HH

#include <vector>
#include <string>
#include "Lane.hh"
#include "InputZone.hh"
#include "OutputZone.hh"
/**
 * Represents an intersection of multiple lanes. 
 * This class is mostly for initializing lanes and zones during startup, it has no function during the simulation. 
 */
class Intersection
{
private:
    /**
     * List of all lanes that pass through this intersection, indexed by direction, then left to right
     */
    std::vector<Lane *> lanes[4];
    /**
     * List of all output zones that lie directly after this intersection, grouped by direction
     */
    Lane *output[4];
    /**
     * List of all input zones that feed the lanes of this intersection, grouped by direction
     */
    Lane *input[4];
public:
    /**
     * Creates an empty intersection
     */
    Intersection();
    ~Intersection();
    /**
     * Returns the nth lane in the given direction, indexed from left to right
     */
    Lane& getLane(Direction dir, int id);
    /**
     * Adds a lane to the intersection, to the right of any existing lanes in the same direction
     * @param dir which way the lane is heading
     * @param through The traffic light that controls vehicles going straight or turning right
     * @param left The traffic light that controls vehicles turning left
     * @param lanelength Length of the lane in feet.
     */
    Intersection& addLane(Direction dir, TrafficLight &through, TrafficLight &left, double lanelength);
    /**
     * Adds an input zone that feeds into all the lanes in this intersection
     * @param dir which way the zone is heading
     * @param id zone ID
     * @param lambda controls arrival rate of created input zone 
     */
    Intersection& addInputZone(Direction dir, int id, double lambda);
    /**
     * Adds an output zone that captures all cars passing through this intersection in the given direction
     * @param dir which way the zone is heading
     * @param id zone ID
     */
    Intersection& addOutputZone(Direction dir, int id);
    /**
     * Connects a lane in the intersection to all lanes in another intersection
     * @param d which way the lanes are heading
     * @param id ID of the lane to connect (numbered left to right)
     * @param other intersection to connect to
     */
    void connectStraight(Direction d, int id, Intersection *other);
    /**
     * Connects the rightmost lane in the intersection to all lanes in another, creating a right turn lane
     * @param d which way the lane (in this intersection) is heading
     * @param other intersection to connect to
     */
    void connectRight(Direction d, Intersection *other);
    /**
     * Connects the leftmost lane in the intersection to all lanes in another, creating a left turn lane
     * @param d which way the lane (in this intersection) is heading
     * @param other intersection to connect to
     */
    void connectLeft(Direction d, Intersection *other);
    /**
     * Calculate the set of reachable zones for all lanes of this intersection. Must be called before simulation starts
     */
    void calcWaypoints();
    /**
     * Print the set of reachable lanes for all lanes of this intersection
     */
    void debugRoutes();
    /**
     * Print a string representation of this intersection
     */ 
    std::string toString();
};
#endif	/* INTERSECTION_HH */

