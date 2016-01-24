#ifndef EVENTQUEUE_HH
#define EVENTQUEUE_HH

#include <queue>
#include <vector>
#include "Events/Event.hh"

/**
 * Implements the Future Event List (FEL) for event-oriented simulation
 */
class EventQueue
{
private:
    /**
     * Priority queue of events
     */
    std::priority_queue<Event*, std::vector<Event*>, EventCompare> queue;
    /**
     * Tracks total number of events processed
     */
    uint64_t eventsProcessed;
    /**
     * Current simulation time
     */
    Tick now;
public:
    /**
     * Creates an empty event queue
     */
    EventQueue();
    /**
     * Inserts an event into the queue at the appropriate time
     * EventQueue is responsible for deleting the event
     */
    void insert(Event *e);
    /**
     * Calls process() on the first event in the queue, then deletes the event
     * @return true if an event was processed, or false if there are no events left in the queue
     */
    bool processNext();
    /**
     * Clears all events from the queue
     */
    void clear();
    /**
     * Returns the number of events processed
     */
    uint64_t getEventsProcessed();
    /**
     * Returns the current tick in simulated time
     */
    Tick Now();
};

// Global event queue declared in main
extern EventQueue eventQueue;

#endif