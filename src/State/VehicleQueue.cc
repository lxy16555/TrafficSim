/*
 * File:   VehicleQueue.cc
 * Author: ehein6
 *
 * Created on January 28, 2015, 5:22 PM
 */

#include "VehicleQueue.hh"

VehicleQueue::VehicleQueue(int s)
: maxSize(s)
{

}

bool
VehicleQueue::isFull() const
{
    return vehicles.size() >= maxSize;
}

bool
VehicleQueue::isEmpty() const
{
    return vehicles.size() == 0;
}

void
VehicleQueue::insert(Vehicle *v)
{
    assert(!isFull());
    vehicles.push_back(v);
}

Vehicle *
VehicleQueue::removeFront()
{
    assert(!isEmpty());
    Vehicle *v = vehicles.front();
    vehicles.pop_front();
    return v;
}

int
VehicleQueue::getSize() const
{
    return vehicles.size();
}

const Vehicle *
VehicleQueue::front() const
{
    return vehicles.front();
}

