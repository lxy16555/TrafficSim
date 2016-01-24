/*
 * File:   StatTracker.hh
 * Author: ehein6
 *
 * Created on February 3, 2015, 2:43 PM
 */

#ifndef STATTRACKER_HH
#define	STATTRACKER_HH

#include <map>
#include <string>
#include <stdio.h>

#include "Log.hh"

class StatTracker {
public:

    StatTracker(std::string filename);
    ~StatTracker();
    /**
     * Records the travel time of a single vehicle
     * @param travelTime seconds the vehicle was in the system
     * @param src source zone
     * @param dest destination zone
     * @return
     */
    void recordTravelTime(float travelTime, int src, int dest);

    /**
     * Returns the mean travel time between two zones
     * @param src
     * @param dest
     * @return
     */
    float getMeanTravelTime(int src, int dest);
    /**
     * Returns the number of cars that went from src to dest
     * @param src
     * @param dest
     * @return
     */
    int getNumberOfTrips(int src, int dest);

private:
    FILE *file;

    /**
     * Sum of all travel times indexed by src, dest
     */
    std::map<int, std::map<int, float> > sums;
    /**
     * Number of vehicles that completed the trip indexed by src, dest
     */
    std::map<int, std::map<int, int> > nums;
};

// Global stat tracker declared in main
extern StatTracker statTracker;

#endif	/* STATTRACKER_HH */

