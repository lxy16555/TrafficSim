/* 
 * File:   TrafficLight.cc
 * Author: ehein6
 * 
 * Created on January 28, 2015, 2:17 PM
 */

#include "TrafficLight.hh"
#include "../Events/TrafficLightChangeEvent.hh"
#include "../EventQueue.hh"
#include "../Log.hh"

TrafficLight::TrafficLight(int id, float greenTime, float yellowTime, float redTime, float initTime)
{
    this->id = id;
    timings[RED] = redTime;
    timings[GREEN] = greenTime;
    timings[YELLOW] = yellowTime;
    
    // TODO randomly set starting color, don't forget to set nextChange accordingly
    // TODO set according to synchronization timing
     // TODO 11th st lights should probably be staggered
    // TODO remember 14 st eastbound cycle is 200 sec
    color = GREEN;
    
    switch ( id ) {
    case 0:   // 10th st eastbound left turn
        if(initTime > 100){
        initTime = initTime - 100;

        }
        if(initTime < 8){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] - initTime);
        }
        else if(initTime < 9.8){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(100 - initTime);
        }
        break;
    case 1:   // 10 st eastbound through light
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 11.6){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(11.6 - initTime);
        }
        else if(initTime < 41.2){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(11.6 + timings[GREEN] - initTime);
        }
        else if(initTime < 45){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(11.6 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(111.6 - initTime);
        }
        break;
    case 2:  // 10 st westbound left turn
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 5){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] - initTime);
        }
        else if(initTime < 8.6){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(100 - initTime);
        }
        break;
    case 3:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 12.8){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(12.8 - initTime);
        }
        else if(initTime < 41.2){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(12.8 + timings[GREEN] - initTime);
        }
        else if(initTime < 45){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(12.8 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(112.8 - initTime);
        }
        break;
    case 4:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 46.9){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(46.9 - initTime);
        }
        else if(initTime < 53.9){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(46.9 + timings[GREEN] - initTime);
        }
        else if(initTime < 57.5){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(46.9 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(146.9 - initTime);
        }
        break;
    case 5:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 59.7){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(59.7 - initTime);
        }
        else if(initTime < 94.4){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(59.7 + timings[GREEN] - initTime);
        }
        else if(initTime < 98){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(59.7 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(159.7 - initTime);
        }
        break;
    case 6:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 20.3){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] - initTime);
        }
        else if(initTime < 23.9){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(100 - initTime);
        }
        break;
    case 7:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 26){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(26 - initTime);
        }
        else if(initTime < 67.5){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(26 + timings[GREEN] - initTime);
        }
        else if(initTime < 70.7){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(26 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(126 - initTime);
        }
        break;
    case 8:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 27.3){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] - initTime);
        }
        else if(initTime < 30.9){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(100 - initTime);
        }
        break;
    case 9:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 33.3){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(33.3 - initTime);
        }
        else if(initTime < 94.4){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(33.3 + timings[GREEN] - initTime);
        }
        else if(initTime < 97.6){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(33.3 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(133.3 - initTime);
        }
        break;
    case 10:
        if(initTime < 9.4){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] - initTime);
        }
        else if(initTime < 13){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(200 - initTime);
        }
        break;
    case 11:
        if(initTime < 100){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(100 - initTime);
        }
        else if(initTime < 136.1){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(100 + timings[GREEN] - initTime);
        }
        else if(initTime < 139.8){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(100 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(300 - initTime);
        }

        break;
    case 12:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 15){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(15 - initTime);
        }
        else if(initTime < 37.4){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(15 + timings[GREEN] - initTime);
        }
        else if(initTime < 41.1){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(15 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(115 - initTime);
        }
        break;
    case 13:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 43.2){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(43.2 - initTime);
        }
        else if(initTime < 51.8){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(43.2 + timings[GREEN] - initTime);
        }
        else if(initTime < 55.4){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(43.2 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(143.2 - initTime);
        }
        break;
    case 14:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 59){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(59 - initTime);
        }
        else if(initTime < 93.7){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(59 + timings[GREEN] - initTime);
        }
        else if(initTime < 96.9){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(59 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(159 - initTime);
        }
        break;
    case 15:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 43.2){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(43.2 - initTime);
        }
        else if(initTime < 54.4){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(43.2 + timings[GREEN] - initTime);
        }
        else if(initTime < 58){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(43.2 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(143.2 - initTime);
        }
        break;
    case 16:
        if(initTime > 100){
        initTime = initTime - 100;
        }
        if(initTime < 59){
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(59 - initTime);
        }
        else if(initTime < 94.7){
            color = GREEN;
            nextChange = eventQueue.Now() + secondsToTicks(59 + timings[GREEN] - initTime);
        }
        else if(initTime < 97.9){
            color = YELLOW;
            nextChange = eventQueue.Now() + secondsToTicks(59 + timings[GREEN] + timings[YELLOW] - initTime);
        }
        else{
            color = RED;
            nextChange = eventQueue.Now() + secondsToTicks(159 - initTime);
        }
        break;
    default:
        break;
    }
    
    eventQueue.insert(
        new TrafficLightChangeEvent(nextChange, *this)
    );
    
    //LOG("Created traffic light %i\n", id);
}

TrafficLight::TrafficLight(int id, bool dummy)
{
    if(dummy){
    this->id = id;
    color = GREEN;
    }
    else{
    this->id = id;
    color = RED;
    }
    //LOG("Created dummy traffic light %i\n", id);
}

TrafficLight::TrafficLight(TrafficLight &other) {}

int 
TrafficLight::getId()
{
    return id;
}

void
TrafficLight::scheduleNext()
{
    nextChange = eventQueue.Now() + secondsToTicks(timings[color]);
    eventQueue.insert(
        new TrafficLightChangeEvent(nextChange, *this)
    );
}
void 
TrafficLight::change()
{
    Color before = color;
    switch (color)
    {
        case RED:       color = GREEN; break;
        case YELLOW:    color = RED; break;
        case GREEN:     color = YELLOW; break;
    }
    Color after = color;
    LOG("Traffic light %i changes from %s to %s\n",
        id,
        TrafficLight::colorToString(before).c_str(),
        TrafficLight::colorToString(after).c_str());
}

Tick 
TrafficLight::getNextChange()
{
    return nextChange;
}

Tick 
TrafficLight::getNextGreen()
{
    switch(color)
    {
        case RED: return nextChange;
        case YELLOW: return nextChange + timings[RED];
        case GREEN: return nextChange + timings[YELLOW] + timings[RED];
    }
}

Tick
TrafficLight::getNextRed()
{
	switch(color)
	{
		case RED: return nextChange + timings[GREEN] + timings[YELLOW];
		case YELLOW: return nextChange;
		case GREEN: return nextChange + timings[YELLOW];
	}
}


TrafficLight::Color
TrafficLight::getColor()
{
    return color;
};

std::string
TrafficLight::colorToString(Color c)
{
    switch (c)
    {
        case RED: return "red";
        case YELLOW: return "yellow";
        case GREEN: return "green";
    }
}

