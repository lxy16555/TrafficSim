/* 
 * File:   SimControlEvent.cc
 * Author: ehein6
 * 
 * Created on January 26, 2015, 11:09 AM
 */

#include "SimControlEvent.hh"
#include "../EventQueue.hh"
#include "../Log.hh"
#include <stdio.h>

SimControlEvent::SimControlEvent(Tick when, ActionType t) 
: Event(when),
  type(t) {
}

void SimControlEvent::process() {
    // Clear the event queue to terminate the simulation
    switch (type)
    {
        case PRINT:
            LOG("Now = %" PRIu64 ", processed %" PRIu64 " events.\n", when, eventQueue.getEventsProcessed());
            break;
        case STOP: 
            LOG("Terminating simulation at time %" PRIu64 ", processed %" PRIu64 " events.\n" , when, eventQueue.getEventsProcessed());
            eventQueue.clear();
            break;
    }
}

std::string SimControlEvent::toString()
{
    std::ostringstream oss;
    oss << when << ": ";
    switch (type)
    {
        case PRINT:
            oss << "SimControlEvent PRINT"; 
            break;
        case STOP: 
            oss << "SimControlEvent STOP"; 
            break;
    }
    return oss.str();
}