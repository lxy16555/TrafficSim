#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "Log.hh"
#include "EventQueue.hh"
#include "StatTracker.hh"
#include "RandomVar.hh"

#include "Events/SimControlEvent.hh"

#include "State/TrafficLight.hh"
#include "State/Intersection.hh"
#include "State/InputZone.hh"
#include "State/OutputZone.hh"

// Global variables
EventQueue eventQueue;
StatTracker statTracker("results.csv");

void initTest()
{  
    //14th eastbound
    TrafficLight *light14ELT = new TrafficLight(10, 9.4, 3.6, 187, 0);
    TrafficLight *light14ETR = new TrafficLight(11, 36.1, 3.7, 60.2, 0);
    //14th westbound (no left turn light)
    TrafficLight *light14WTR = new TrafficLight(12, 22.3, 3.7, 74, 0);
    //14th northbound
    TrafficLight *light14NLT = new TrafficLight(13, 8.8, 3.6, 87.6, 0);
    TrafficLight *light14NTR = new TrafficLight(14, 34.7, 3.2, 62.1, 0);
    //14th southbound
    TrafficLight *light14SLT = new TrafficLight(15, 11.2, 3.6, 85.2, 0);
    TrafficLight *light14STR = new TrafficLight(16, 35.7, 3.2, 61.1, 0);
    
    Intersection *i = new Intersection();
    i->
    	 addLane(NORTH, *light14NTR, *light14NLT, 200)
        .addInputZone(NORTH, 1, 0.15)
        .addOutputZone(NORTH, 2)

        .addLane(SOUTH, *light14STR, *light14SLT, 200)
        .addInputZone(SOUTH, 3, 0.15)
        .addOutputZone(SOUTH, 4)
    
        .addLane(EAST, *light14WTR, *light14WTR, 200)
        .addInputZone(EAST, 5, 0.15)
        .addOutputZone(EAST, 6)

        .addLane(WEST, *light14ETR, *light14ELT, 200)
        .addInputZone(WEST, 7, 0.15)
        .addOutputZone(WEST, 8)
    ;

    i->connectLeft(NORTH, NULL);
    i->connectLeft(SOUTH, NULL);
    i->connectLeft(EAST, NULL);
    i->connectLeft(WEST, NULL);
    
    i->connectRight(NORTH, NULL);
    i->connectRight(SOUTH, NULL);
    i->connectRight(EAST, NULL);
    i->connectRight(WEST, NULL);
    
    i->connectStraight(NORTH, 0,  NULL);
    i->connectStraight(SOUTH, 0, NULL);
    i->connectStraight(EAST, 0, NULL);
    i->connectStraight(WEST, 0, NULL);
    
    i->calcWaypoints();
    
    LOG("%s", i->toString().c_str());
    
    i->debugRoutes();
    
}

void initPeachtree(float init10th, float init11th, float init12th, float init13th, float init14th)
{
    LOG("Initializing traffic network...\n");

    // Dummy-lights to model no left turn
    TrafficLight *dummyRed = new TrafficLight(-2, false);
    TrafficLight *dummyGreen = new TrafficLight(-3, true);

    Intersection *peachtreeAnd14th = new Intersection();
    Intersection *peachtreeAnd13th = new Intersection();
    Intersection *peachtreeAnd12th = new Intersection();
    Intersection *peachtreeAnd11th = new Intersection();
    Intersection *peachtreeAnd10th = new Intersection();

    //14th eastbound
    TrafficLight *light14ELT = new TrafficLight(10, 9.4, 3.6, 187, init14th);
    TrafficLight *light14ETR = new TrafficLight(11, 36.1, 3.7, 60.2, init14th);
    //14th westbound (no left turn light)
    TrafficLight *light14WTR = new TrafficLight(12, 22.3, 3.7, 74, init14th);
    //14th northbound
    TrafficLight *light14NLT = new TrafficLight(13, 8.8, 3.6, 87.6, init14th);
    TrafficLight *light14NTR = new TrafficLight(14, 34.7, 3.2, 62.1, init14th);
    //14th southbound
    TrafficLight *light14SLT = new TrafficLight(15, 11.2, 3.6, 85.2, init14th);
    TrafficLight *light14STR = new TrafficLight(16, 35.7, 3.2, 61.1, init14th);
    double lanelength1314 = 351;
    double lanelength1213 = 377;
    double lanelength1112 = 423;
    double lanelength1011 = 430;
    // Missing lane lengths for outer lanes
    double lanelengthOuter = 200;
    peachtreeAnd14th->
    	 addLane(NORTH, *light14NTR, *light14NLT, lanelength1314)
    	.addLane(NORTH, *light14NTR, *dummyRed, lanelength1314)
    	.addLane(NORTH, *light14NTR, *dummyRed, lanelength1314)
        .addOutputZone(NORTH, 214)

        .addLane(SOUTH, *light14STR, *light14SLT, lanelength1314)
        .addLane(SOUTH, *light14STR, *dummyRed, lanelength1314)
        .addLane(SOUTH, *light14STR, *dummyRed, lanelength1314)
        .addInputZone(SOUTH, 114, 0.2913)

        .addLane(EAST, *light14WTR, *light14WTR, lanelengthOuter)
        .addLane(EAST, *light14WTR, *dummyRed, lanelengthOuter)
        .addInputZone(EAST, 115, 0.1213)
        .addOutputZone(EAST, 213)

        .addLane(WEST, *light14ETR, *light14ELT, lanelengthOuter)
        .addLane(WEST, *light14ETR, *dummyRed, lanelengthOuter)
        .addLane(WEST, *light14ETR, *dummyRed, lanelengthOuter)
        .addInputZone(WEST, 113, 0.0287)
        .addOutputZone(WEST, 215)
    ;

    peachtreeAnd13th->
         addLane(WEST, *dummyGreen, *dummyGreen, lanelengthOuter)
        .addInputZone(WEST, 112, 0.0154)

        .addLane(NORTH, *dummyGreen, *dummyRed, lanelength1213)
        .addLane(NORTH, *dummyGreen, *dummyRed, lanelength1213)
        .addLane(NORTH, *dummyGreen, *dummyRed, lanelength1213)

        .addLane(SOUTH, *dummyGreen, *dummyGreen, lanelength1314)
        .addLane(SOUTH, *dummyGreen, *dummyRed, lanelength1314)

        .addOutputZone(WEST, 212)
    ;
    // 12th east and westbound
    TrafficLight *light12EWTR = new TrafficLight(8, 27.3, 3.6, 69.1, init12th);
    // 12th north and southbound
    TrafficLight *light12NSTR = new TrafficLight(9, 61.1, 3.2, 35.7, init12th);
    peachtreeAnd12th->
         addLane(NORTH, *light12NSTR, *light12NSTR, lanelength1112)
        .addLane(NORTH, *light12NSTR, *dummyRed, lanelength1112)
        .addLane(NORTH, *light12NSTR, *dummyRed, lanelength1112)

        .addLane(SOUTH, *light12NSTR, *light12NSTR, lanelength1213)
        .addLane(SOUTH, *light12NSTR, *dummyRed, lanelength1213)
        .addLane(SOUTH, *light12NSTR, *dummyRed, lanelength1213)

        .addLane(EAST, *light12EWTR, *light12EWTR, lanelengthOuter)
        .addLane(EAST, *light12EWTR, *dummyRed, lanelengthOuter)
        .addInputZone(EAST, 121, 0.0158)
        .addOutputZone(EAST, 206)

        .addLane(WEST, *light12EWTR, *light12EWTR, lanelengthOuter)
        .addInputZone(WEST, 106, 0.0011)
        .addOutputZone(WEST, 221)
    ;
    // 11th east and westbound
    TrafficLight *light11ETR = new TrafficLight(6, 20.3, 3.6, 76.1, init11th);
    TrafficLight *light11WTR = new TrafficLight(6, 20.3, 3.6, 76.1, init11th +10);
    //11th north and southbound
    TrafficLight *light11NTR = new TrafficLight(7, 41.5, 3.2, 55.3, init11th + 10);
    TrafficLight *light11STR = new TrafficLight(7, 41.5, 3.2, 55.3, init11th + 25);
    peachtreeAnd11th->
         addLane(NORTH, *light11NTR, *light11NTR, lanelength1011)
        .addLane(NORTH, *light11NTR, *dummyRed, lanelength1011)

        .addLane(SOUTH, *light11STR, *light11STR, lanelength1112)
        .addLane(SOUTH, *light11STR, *dummyRed, lanelength1112)
        .addLane(SOUTH, *light11STR, *dummyRed, lanelength1112)

        .addLane(EAST, *light11ETR, *light11ETR, lanelengthOuter)
        .addLane(EAST, *light11ETR, *dummyRed, lanelengthOuter)
        .addInputZone(EAST, 122, 0.0545)
        .addOutputZone(EAST, 203)

        .addLane(WEST, *light11WTR, *light11WTR, lanelengthOuter)
        .addInputZone(WEST, 103, 0.0099)
        .addOutputZone(WEST, 222)
    ;
    // 10th st
    // Eastbound
    TrafficLight *light10ELT = new TrafficLight(0, 8.0, 1.8, 90.2, init10th);
    TrafficLight *light10ETR = new TrafficLight(1, 29.6, 3.8, 66.6, init10th);
    // Westbound
    TrafficLight *light10WLT = new TrafficLight(2, 5.0, 3.6, 91.4, init10th);
    TrafficLight *light10WTR = new TrafficLight(3, 28.4, 3.8 ,67.8, init10th);
    // North and southbound (same timings)
    TrafficLight *light10NSLT = new TrafficLight(4, 7.0, 3.6, 89.4, init10th);
    TrafficLight *light10NSTR = new TrafficLight(5, 34.7, 3.6, 61.7, init10th);
    peachtreeAnd10th->
         addLane(NORTH, *light10NSTR, *light10NSLT, lanelengthOuter)
        .addLane(NORTH, *light10NSTR, *dummyRed, lanelengthOuter)
        .addLane(NORTH, *light10NSTR, *dummyRed, lanelengthOuter)
        .addInputZone(NORTH, 101, 0.1597)

        .addLane(SOUTH, *light10NSTR, *light10NSLT, lanelength1112)
        .addLane(SOUTH, *light10NSTR, *dummyRed, lanelength1112)
        .addLane(SOUTH, *light10NSTR, *dummyRed, lanelength1112)
        .addOutputZone(SOUTH, 201)

        .addLane(EAST, *light10ETR, *light10ELT, lanelengthOuter)
        .addLane(EAST, *light10ETR, *dummyRed, lanelengthOuter)
        .addLane(EAST, *light10ETR, *dummyRed, lanelengthOuter)
        .addLane(EAST, *light10ETR, *dummyRed, lanelengthOuter)
        .addInputZone(EAST , 123, 0.0655)
        .addOutputZone(EAST, 202)

        .addLane(WEST, *light10WTR, *light10WLT, lanelengthOuter)
        .addLane(WEST, *light10WTR, *dummyRed, lanelengthOuter)
        .addLane(WEST, *light10WTR, *dummyRed, lanelengthOuter)
        .addInputZone(WEST , 102, 0.0369)
        .addOutputZone(WEST, 223)
    ;

    // Connect all straight lanes together
    peachtreeAnd10th->connectStraight(NORTH, 1, peachtreeAnd11th);
    peachtreeAnd10th->connectStraight(NORTH, 2, peachtreeAnd11th);
    peachtreeAnd10th->connectStraight(SOUTH, 1, NULL);
    peachtreeAnd10th->connectStraight(SOUTH, 2, NULL);
    peachtreeAnd10th->connectStraight(EAST, 1, NULL);
    peachtreeAnd10th->connectStraight(EAST, 2, NULL);
    peachtreeAnd10th->connectStraight(EAST, 3, NULL);
    peachtreeAnd10th->connectStraight(WEST, 1, NULL);
    peachtreeAnd10th->connectStraight(WEST, 2, NULL);

    peachtreeAnd11th->connectStraight(NORTH, 0, peachtreeAnd12th);
    peachtreeAnd11th->connectStraight(NORTH, 1, peachtreeAnd12th);
    peachtreeAnd11th->connectStraight(SOUTH, 0, peachtreeAnd10th);
    peachtreeAnd11th->connectStraight(SOUTH, 1, peachtreeAnd10th);
    peachtreeAnd11th->connectStraight(SOUTH, 2, peachtreeAnd10th);
    peachtreeAnd11th->connectStraight(EAST, 0, NULL);
    peachtreeAnd11th->connectStraight(WEST, 0, NULL);

    peachtreeAnd12th->connectStraight(NORTH, 1, peachtreeAnd13th);
    peachtreeAnd12th->connectStraight(NORTH, 2, peachtreeAnd13th);
    peachtreeAnd12th->connectStraight(SOUTH, 1, peachtreeAnd11th);
    peachtreeAnd12th->connectStraight(SOUTH, 2, peachtreeAnd11th);
    peachtreeAnd12th->connectStraight(EAST, 1, NULL);
    peachtreeAnd12th->connectStraight(WEST, 0, NULL);

    peachtreeAnd13th->connectStraight(NORTH, 0, peachtreeAnd14th);
    peachtreeAnd13th->connectStraight(NORTH, 1, peachtreeAnd14th);
    peachtreeAnd13th->connectStraight(NORTH, 2, peachtreeAnd14th);
    peachtreeAnd13th->connectStraight(SOUTH, 0, peachtreeAnd12th);
    peachtreeAnd13th->connectStraight(SOUTH, 1, peachtreeAnd12th);

    peachtreeAnd14th->connectStraight(NORTH, 1, NULL);
    peachtreeAnd14th->connectStraight(NORTH, 2, NULL);
    peachtreeAnd14th->connectStraight(SOUTH, 1, peachtreeAnd13th);
    peachtreeAnd14th->connectStraight(SOUTH, 2, peachtreeAnd13th);
    peachtreeAnd14th->connectStraight(EAST, 1, NULL);
    peachtreeAnd14th->connectStraight(WEST, 1, NULL);
    peachtreeAnd14th->connectStraight(WEST, 2, NULL);

    // Connect all rightturn lanes
    peachtreeAnd10th->connectRight(NORTH, NULL);
    peachtreeAnd10th->connectRight(SOUTH, NULL);
    peachtreeAnd10th->connectRight(EAST, NULL);
    peachtreeAnd10th->connectRight(WEST, peachtreeAnd11th);

    peachtreeAnd11th->connectRight(NORTH, NULL);
    peachtreeAnd11th->connectRight(SOUTH, NULL);
    peachtreeAnd11th->connectRight(EAST, peachtreeAnd10th);
    peachtreeAnd11th->connectRight(WEST, peachtreeAnd12th);

    peachtreeAnd12th->connectRight(NORTH, NULL);
    peachtreeAnd12th->connectRight(SOUTH, NULL);
    peachtreeAnd12th->connectRight(EAST, peachtreeAnd11th);
    peachtreeAnd12th->connectRight(WEST, peachtreeAnd13th);

    peachtreeAnd13th->connectRight(NORTH, NULL);
    peachtreeAnd13th->connectRight(WEST, peachtreeAnd14th);

    peachtreeAnd14th->connectRight(NORTH, NULL);
    peachtreeAnd14th->connectRight(SOUTH, NULL);
    peachtreeAnd14th->connectRight(EAST, peachtreeAnd13th);
    peachtreeAnd14th->connectRight(WEST, NULL);


    // Connect all leftturn lanes
    peachtreeAnd10th->connectLeft(NORTH, NULL);
    peachtreeAnd10th->connectLeft(SOUTH, NULL);
    peachtreeAnd10th->connectLeft(EAST, peachtreeAnd11th);
    peachtreeAnd10th->connectLeft(WEST, NULL);

    peachtreeAnd11th->connectLeft(NORTH, NULL);
    peachtreeAnd11th->connectLeft(SOUTH, NULL);
    peachtreeAnd11th->connectLeft(EAST, peachtreeAnd12th);
    peachtreeAnd11th->connectLeft(WEST, peachtreeAnd10th);

    peachtreeAnd12th->connectLeft(NORTH, NULL);
    peachtreeAnd12th->connectLeft(SOUTH, NULL);
    peachtreeAnd12th->connectLeft(EAST, peachtreeAnd13th);
    peachtreeAnd12th->connectLeft(WEST, peachtreeAnd11th);

    peachtreeAnd13th->connectLeft(SOUTH, NULL);
    peachtreeAnd13th->connectLeft(WEST, peachtreeAnd12th);

    peachtreeAnd14th->connectLeft(NORTH, NULL);
    peachtreeAnd14th->connectLeft(SOUTH, NULL);
    peachtreeAnd14th->connectLeft(EAST, NULL);
    peachtreeAnd14th->connectLeft(WEST, peachtreeAnd13th);


    // Calculate routes through the network for each lane
    peachtreeAnd10th->calcWaypoints();
    peachtreeAnd11th->calcWaypoints();
    peachtreeAnd12th->calcWaypoints();
    peachtreeAnd13th->calcWaypoints();
    peachtreeAnd14th->calcWaypoints();

    // Print out the intersections for debug
    LOG("%s", peachtreeAnd14th->toString().c_str());
    LOG("%s", peachtreeAnd13th->toString().c_str());
    LOG("%s", peachtreeAnd12th->toString().c_str());
    LOG("%s", peachtreeAnd11th->toString().c_str());
    LOG("%s", peachtreeAnd10th->toString().c_str());

    // Print out the intersections for debug
    LOG("\nPeachtree and 14th:\n");
    peachtreeAnd14th->debugRoutes();
    LOG("\nPeachtree and 13th:\n");
    peachtreeAnd13th->debugRoutes();
    LOG("\nPeachtree and 12th:\n");
    peachtreeAnd12th->debugRoutes();
    LOG("\nPeachtree and 11th:\n");
    peachtreeAnd11th->debugRoutes();
    LOG("\nPeachtree and 10th:\n");
    peachtreeAnd10th->debugRoutes();
}

int main(int argc, char *argv[])
{
    struct timeval t;
    gettimeofday(&t, NULL);
    RandomVar::seed(t.tv_usec);

    // Parse command line arguments to choose light synchronization mode
    //   async   : random offset between lights
    //   sync N  : stagger adjacent intersections by N seconds
    enum Mode {ASYNC, SYNC};
    Mode mode;
    int initTime;



    if      ( argc == 2 && std::string(argv[1]) == "async")
    {
        mode = ASYNC;
    }
    else if ( argc == 3 && std::string(argv[1]) == "sync")
    {
        mode = SYNC;
        initTime = atoi(argv[2]);
    }
    else
    {
        fprintf(stderr, "Usage: ./trafficSim async|sync [initTime]\n");
        return -1;
    }
    
    // Build the traffic network
    //initTest();
    if (mode == SYNC) {
        initPeachtree(
            0,
            1*initTime % 200,
            2*initTime % 200,
            3*initTime % 200,
            4*initTime % 200
        );
    } else if (mode == ASYNC) {
        initPeachtree(
            RandomVar::initSignal(),
            RandomVar::initSignal(),
            RandomVar::initSignal(),
            RandomVar::initSignal(),
            RandomVar::initSignal()
        );
    }
    
    LOG("Loading routing probabilities...\n");
    InputZone::initRoutingProbabilities();

    // Schedule the end of the simulation
    eventQueue.insert(new SimControlEvent(secondsToTicks(15 * 60), SimControlEvent::STOP));
    // Main simulator loop
    while(eventQueue.processNext());

    LOG("Exiting simulator...\n");

    return 0;
}
