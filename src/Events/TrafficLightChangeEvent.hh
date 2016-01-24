
#ifndef TRAFFICLIGHTCHANGEEVENT_HH
#define	TRAFFICLIGHTCHANGEEVENT_HH

#include "Event.hh"
#include "../State/TrafficLight.hh"

/**
 * Handles the changing of a traffic light
 */
class TrafficLightChangeEvent : public Event {
public:
    TrafficLightChangeEvent(Tick when, TrafficLight& t);
    virtual void process();
    virtual std::string toString();
private:
    /**
     * The light to change
     */
    TrafficLight &trafficLight;
};

#endif	/* TRAFFICLIGHTCHANGE_HH */

