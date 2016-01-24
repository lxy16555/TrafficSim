/* 
 * File:   SimControlEvent.hh
 * Author: ehein6
 *
 * Created on January 26, 2015, 11:09 AM
 */

#ifndef SIMCONTROLEVENT_HH
#define	SIMCONTROLEVENT_HH

#include "Event.hh"
#include "../EventQueue.hh"
/**
 * Special event for controlling the simulation
 * In particular, the STOP event clears all future events from the event queue
 */
class SimControlEvent : public Event {
public:

    enum ActionType {PRINT, STOP};
    SimControlEvent(Tick when, ActionType t);
    virtual void process();
    virtual std::string toString();
private:
    ActionType type;
};

#endif	/* SIMCONTROLEVENT_HH */

