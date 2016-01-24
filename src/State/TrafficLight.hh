/* 
 * File:   TrafficLight.hh
 * Author: ehein6
 *
 * Created on January 28, 2015, 2:17 PM
 */

#ifndef TRAFFICLIGHT_HH
#define	TRAFFICLIGHT_HH

#include <string>
#include "../Ticks.hh"

class TrafficLight {
public:    
    enum Color {RED = 0, GREEN = 1, YELLOW = 2};
private:
    /**
     * ID of this light
     */
    int id;
    /**
     * Color of this light
     */
    Color color;
    /**
     * Timings for this light, indexed by color
     */
    float timings[3];
    
    /**
     * Absolute time when this light will change next
     */
    Tick nextChange;
    /**
     * Disallow copying of traffic lights
     */
    TrafficLight(TrafficLight &other);
public:
    /**
     * Creates a traffic light 
     * @param id ID of the traffic light
     * @param greenTime number of seconds the light will stay green
     * @param yellowTime number of seconds the light will stay yellow
     * @param redTime number of seconds the light will stay red
     * @param initTime skip this number of seconds into the light change cycle, offsetting this light from the rest
     */
    TrafficLight(int id, float greenTime, float yellowTime, float redTime, float initTime);
    /**
     * Creates a dummy traffic light, useful as a placeholder.
     * No transitions are scheduled for a dummy light
     * @param id ID of the traffic light
     * @param dummy true for always green or false for always red
     */
    TrafficLight(int id, bool dummy);
    /**
     * Returns the ID of the traffic light
     */ 
    int getId();
    /**
     * Schedules the next transition for the traffic light
     */
    void scheduleNext();
    /**
     * Change the color of the light
     */
    void change();
    /**
     * Get the timing for the next change
     * @return 
     */
    Tick getNextChange();
    /**
     * Get the absolute time when this light will be green next
     */
    Tick getNextGreen();
    /**
     * Get the absolute time when this light will be red next
     */
    Tick getNextRed();
    /**
     * Get the color of this light
     */
    Color getColor();
    /**
     * Convert the light color enum to a string
     */
    static std::string colorToString(Color c);
    
};

#endif	/* TRAFFICLIGHT_HH */

