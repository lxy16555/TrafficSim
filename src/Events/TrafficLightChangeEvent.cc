/* 
 * File:   VehicleArriveEvent.cc
 * Author: ehein6
 * 
 * Created on January 26, 2015, 3:43 PM
 */

#include "TrafficLightChangeEvent.hh"
#include "../Log.hh"
#include "../State/TrafficLight.hh"
#include "../EventQueue.hh"

TrafficLightChangeEvent::TrafficLightChangeEvent(Tick when, TrafficLight &t)
: Event(when),
  trafficLight(t){
}

void TrafficLightChangeEvent::process()
{   
    LOG("At time %" PRIu64 ": ", when);
    // Change the color of the light
    trafficLight.change();   
    // Schedule the next change
    trafficLight.scheduleNext();
}

std::string
TrafficLightChangeEvent::toString()
{
    std::ostringstream oss;
    oss << when << ": "
        << "Traffic Light " << trafficLight.getId() 
        << " (currently " << TrafficLight::colorToString(trafficLight.getColor()) << ") "
        << "changes color.";
    return oss.str();
}