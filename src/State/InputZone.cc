/*
 * File:   InputZone.cc
 * Author: ehein6
 *
 * Created on January 29, 2015, 6:09 PM
 */

#include "InputZone.hh"
#include "../EventQueue.hh"
#include "../Events/VehicleArriveEvent.hh"
#include "../Log.hh"

// "Dummy" light that is always green
TrafficLight InputZone::dummyLight(-1, true);

InputZone::InputZone(int i, Direction dir, double l)
: Lane(dir, dummyLight, dummyLight, 0), id(i), lambda(l), isArriveEventScheduled(false)
{
    scheduleNext();

    if (id == 114 || id == 101) { enableDebug(); }
}

InputZone::~InputZone()
{
    if (debugFile) { fclose(debugFile); }
}

void
InputZone::enableDebug()
{
    debugFile = fopen(("arrivals-" + std::to_string(id) + ".csv").c_str(), "w");
}

void
InputZone::scheduleNext()
{
    if (!isArriveEventScheduled)
    {
        // Get interarrival time and convert to Ticks.
        Tick when = eventQueue.Now() + secondsToTicks(RandomVar::interArr(lambda));
        // Make sure it's not scheduled for this tick
        if (when == eventQueue.Now()) { when++; }

        eventQueue.insert(
            new VehicleArriveEvent(when, *this)
        );
        isArriveEventScheduled = true;

        if (debugFile) { fprintf(debugFile, "%f\n", ticksToSeconds(when - eventQueue.Now()) ); }
    }

    Lane::scheduleNext();
}

int
InputZone::getId() {return id; }

int
InputZone::pickRandomDest()
{

    if (waypoints.size() == 0)
    {
        LOG("Error: No zones reachable from input zone %i!\n", id);
        assert(0);
    }

    // Table of probabilities for this zone
    std::map<int, float> &rp = routingProbabilities.at(id);

    // Sum up the probabilities for all the possible destinations
    float sum;
    for (int w : waypoints)
    {
        sum += rp.at(w);
        //LOG("P(%i) = %f\n", w, sum);
    }

    // Some zones don't have any data, so we'll just pick a random destination
    if (sum == 0)
    {
        int index = RandomVar::getInt(waypoints.size() - 1);
        return waypoints[index];
    }
    else {
    // Roll a random number in the range [0, sum]
    float roll = RandomVar::getDouble(sum);
    //LOG("sum = %f\n", sum);
    // Subtract each weight from the rolled number until it is less than the weight
    for (int w : waypoints)
    {
        //LOG("Pick zone %i? %f < %f\n", w, roll, rp[w]);
        if (roll < rp[w]){
            return w;
        } else {
            roll -= rp[w];
        }
    }
    }
    assert(0);

}

void
InputZone::debugRoutes()
{
    LOG("Zone %i can reach: ", id);;
    for (int w : waypoints)
    {
        LOG("%i, ", w);
    }
    LOG("\n");
}

std::map<int, std::map<int, float> > InputZone::routingProbabilities;

void
InputZone::initRoutingProbabilities()
{
    FILE *in = fopen("outputProb.csv", "r");
    if (in == NULL)
    {
        LOG("Missing zone probabilities in outputProb.csv!\n");
        assert(0);
    }
    int src, dest;
    float prob;
    while (fscanf(in, "%i, %i, %f", &src, &dest, &prob) == 3)
    {
        routingProbabilities[src][dest] = prob;
    }
    fclose(in);
}
