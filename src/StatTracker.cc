/*
 * File:   StatTracker.cc
 * Author: ehein6
 *
 * Created on February 3, 2015, 2:43 PM
 */

#include "StatTracker.hh"

StatTracker::StatTracker(std::string filename)
{
    file = fopen(filename.c_str(),"w");
    if (!file) { LOG("Error: Could not open %s to write results.\n", filename.c_str()); }
    fprintf(file, "Source, Destination, Travel Time\n");
}

StatTracker::~StatTracker()
{
    fclose(file);
}

// TODO dump to csv
void
StatTracker::recordTravelTime(float travelTime, int src, int dest)
{
    fprintf(file, "%i, %i, %f\n", src, dest, travelTime);

    sums[src][dest] += travelTime;
    nums[src][dest] += 1;
}

float
StatTracker::getMeanTravelTime(int src, int dest)
{
    return sums[src][dest] / nums[src][dest];
}

int
StatTracker::getNumberOfTrips(int src, int dest)
{
    return nums[src][dest];
}
