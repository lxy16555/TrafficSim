/* 
 * File:   Event.hh
 * Author: ehein6
 *
 * Created on January 26, 2015, 11:06 AM
 */

#ifndef EVENT_HH
#define	EVENT_HH

#define __STDC_FORMAT_MACROS
#include <stdint.h>

#include <string>
#include <sstream>
#include "../Ticks.hh"

class Event
{
    friend class EventQueue;
    friend class EventCompare;
protected:
    /**
     * Time when this event will occur
     */
    Tick when;
    /**
     * Reference back to the event queue so this event can schedule more events
     */
public:
    explicit Event(Tick w) : when(w) {}
    virtual ~Event() {}
    virtual void process() = 0;
    virtual std::string toString() = 0;
};

// Tells the priority queue how to compare events
struct EventCompare {
    bool operator()(Event *lhs, Event *rhs) { return lhs->when > rhs->when; } 
};

#endif	/* EVENT_HH */

