/* 
 * File:   Vehicle.cc
 * Author: ehein6
 * 
 * Created on January 28, 2015, 5:18 PM
 */

#include "Vehicle.hh"

int Vehicle::nextId = 0;

Vehicle::Vehicle(Tick now, int src, int dst) 
: id(++nextId),
  sourceZone(src),
  destinationZone(dst),
  whenArrived(now){
}

