#include "EventQueue.hh"
#include <assert.h>
#include "Log.hh"

EventQueue::EventQueue() : now(0) {}

void EventQueue::insert(Event *e)
{
    // Don't allow scheduling events in the past
    if (e->when <= now)
    {
        LOG("Tried to schedule event at tick %" PRIu64 ", but now=%" PRIu64 "\n", e->when, now);
        LOG("%s\n", e->toString().c_str());
        assert(0);
    }
    queue.push(e);
}

bool EventQueue::processNext()
{
    if (queue.empty()){
        return false;
    } else {
        
        // Grab the top event from the list
        Event *e = queue.top();
        queue.pop();
        // Move time forwards to this event
        now = e->when;
        // Process the event
        e->process();
        // Delete the event
        delete e;
       
        eventsProcessed += 1;
        return true; 
    }
}

void EventQueue::clear()
{
    while (!queue.empty())
    {
        delete queue.top();
        queue.pop();
    }
}

uint64_t EventQueue::getEventsProcessed()
{
    return eventsProcessed;
}

Tick EventQueue::Now()
{
    return now;
}