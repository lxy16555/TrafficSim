/*
 * File:   Intersection.cc
 * Author: ehein6
 *
 * Created on January 29, 2015, 4:03 PM
 */

#include "Intersection.hh"
#include "../Log.hh"

Intersection::Intersection()
{
    input[NORTH] = NULL;
    input[SOUTH] = NULL;
    input[EAST] = NULL;
    input[WEST] = NULL;

    output[NORTH] = NULL;
    output[SOUTH] = NULL;
    output[EAST] = NULL;
    output[WEST] = NULL;
}

Intersection::~Intersection()
{
    for (Lane *l : lanes[NORTH]) { delete l; }
    for (Lane *l : lanes[SOUTH]) { delete l; }
    for (Lane *l : lanes[EAST]) { delete l; }
    for (Lane *l : lanes[WEST]) { delete l; }
    if (input[NORTH])  { delete input[NORTH]; }
    if (input[SOUTH])  { delete input[SOUTH]; }
    if (input[EAST])   { delete input[EAST]; }
    if (input[WEST])   { delete input[WEST]; }
    if (output[NORTH]) { delete output[NORTH]; }
    if (output[SOUTH]) { delete output[SOUTH]; }
    if (output[EAST])  { delete output[EAST]; }
    if (output[WEST])  { delete output[WEST]; }
}


Lane&
Intersection::getLane(Direction dir, int id)
{
    return *lanes[dir][id];
}

Intersection&
Intersection::addLane(Direction dir, TrafficLight &through, TrafficLight &left, double lanelength)
{
    assert(input[dir] == NULL); // Must add input zones last!
    lanes[dir].push_back(new Lane(dir, through, left, lanelength));
    return *this;
}

Intersection&
Intersection::addInputZone(Direction dir, int id, double lambda)
{
    assert(input[dir] == NULL);
    input[dir] = new InputZone(id, dir, lambda);
    for (Lane *b : lanes[dir])
    {
        input[dir]->connectTo(b);
    }
    return *this;
}

Intersection&
Intersection::addOutputZone(Direction dir, int id)
{
    assert(output[dir] == NULL);
    output[dir] = new OutputZone(id, dir);
    return *this;
}

//TODO add code to connectRight, connectStraight
void
Intersection::connectStraight(Direction d, int id, Intersection *other)
{
	Lane *a = lanes[d][id];
	if(output[d])
		a->connectTo(output[d]);
	else{
		for(Lane *b : other->lanes[d])
		{
			a->connectTo(b);
		}
	}
}

void
Intersection::connectRight(Direction d, Intersection *other)
{
	switch(d){
			case EAST:
			{
				Lane *a = lanes[d][lanes[d].size() - 1];
				if(output[SOUTH])
					a->connectTo(output[SOUTH]);
				else
					for (Lane *b : other->lanes[SOUTH])
					{
						a->connectTo(b);
					}
				break;
			}
			case WEST:
			{
				Lane *a = lanes[d][lanes[d].size() - 1];
					if(output[NORTH])
						a->connectTo(output[NORTH]);
					else
						for (Lane *b : other->lanes[NORTH])
						{
							a->connectTo(b);
						}
				break;
			}
			case NORTH:
			{
				if(output[EAST])
				{
					Lane *lane = lanes[d][lanes[d].size() - 1];
					lane->connectTo(output[EAST]);
				}
				break;
			}
			case SOUTH:
			{
				if(output[WEST])
				{
					Lane *lane = lanes[d][lanes[d].size() - 1];
					lane->connectTo(output[WEST]);
				}
				break;
			}
		}
}

void
Intersection::connectLeft(Direction d, Intersection *other)
{
	switch(d){
		case EAST:
		{
			Lane *a = lanes[d][0];
			if(output[NORTH])
				a->connectTo(output[NORTH]);
			else
				for (Lane *b : other->lanes[NORTH])
				{
					a->connectTo(b);
				}
			//if(output[WEST])
			//	a->connectTo(output[WEST]);
			break;
		}
		case WEST:
		{
			Lane *a = lanes[d][0];
			if(output[SOUTH])
				a->connectTo(output[SOUTH]);
			else
				for (Lane *b : other->lanes[SOUTH])
				{
					a->connectTo(b);
				}
			//if(output[EAST])
			//	a->connectTo(output[EAST]);
			break;
		}
		case NORTH:
		{
			Lane *lane = lanes[d][0];
			if(output[WEST])
			{
				lane->connectTo(output[WEST]);
			}
			//if(output[SOUTH])
			//	lane->connectTo(output[SOUTH]);
			break;
		}
		case SOUTH:
		{
			Lane *lane = lanes[d][0];
			if(output[EAST])
			{
				lane->connectTo(output[EAST]);
			}
			//if(output[NORTH])
			//	lane->connectTo(output[NORTH]);
			break;
		}
	}
}

void
Intersection::calcWaypoints()
{
    for (Lane *l : lanes[NORTH]) { l->calcWaypoints(); }
    for (Lane *l : lanes[SOUTH]) { l->calcWaypoints(); }
    for (Lane *l : lanes[EAST]) { l->calcWaypoints(); }
    for (Lane *l : lanes[WEST]) { l->calcWaypoints(); }
    for (int i = 0; i < 4; ++i)
    {
        if (input[(Direction)i] != NULL)
        {
            input[(Direction)i]->calcWaypoints();
        }
    }
}

void
Intersection::debugRoutes()
{
    std::string s;
    LOG("Northbound lanes:\n");
    for (Lane *l : lanes[NORTH]) { l->debugRoutes(); }
    LOG("Southbound lanes:\n");
    for (Lane *l : lanes[SOUTH]) { l->debugRoutes(); }
    LOG("Eastbound lanes:\n");
    for (Lane *l : lanes[EAST]) { l->debugRoutes(); }
    LOG("Westbound lanes:\n");
    for (Lane *l : lanes[WEST]) { l->debugRoutes(); }
    LOG("Input Zones:\n");
    for (int i = 0; i < 4; ++i)
    {
        if (input[(Direction)i] != NULL)
        {
            input[(Direction)i]->debugRoutes();
        }
    }
}

std::string
Intersection::toString()
{
    unsigned x, y;
    unsigned w = lanes[NORTH].size() + lanes[SOUTH].size() + 8;
    unsigned h = lanes[EAST].size()  + lanes[WEST].size()  + 6;

    // Each element of the vector is a row, index as image[row][col] or image[y][x]
    std::vector<std::string> image(h, std::string(w, ' '));

    // Draw the north/south lanes
    x = 4;
    for (Lane *l : lanes[SOUTH])
    {
        image[0][x] = '|';
        image[1][x] = '|';
        image[2][x] = 'V';

        image[h-3][x] = TrafficLight::colorToString(l->through.getColor())[0];
        image[h-2][x] = '|';
        image[h-1][x] = '|';
        x++;
    }
    for (Lane *l : lanes[NORTH])
    {
        image[0][x] = '|';
        image[1][x] = '|';
        image[2][x] = TrafficLight::colorToString(l->through.getColor())[0];

        image[h-3][x] = '^';
        image[h-2][x] = '|';
        image[h-1][x] = '|';
        x++;
    }

    // Draw the east/west lanes
    y = 3;
    for (Lane *l : lanes[WEST])
    {
        image[y][0] = '-';
        image[y][1] = '-';
        image[y][2] = '-';
        image[y][3] = TrafficLight::colorToString(l->through.getColor())[0];

        image[y][w-4] = '<';
        image[y][w-3] = '-';
        image[y][w-2] = '-';
        image[y][w-1] = '-';
        y++;
    }
    for (Lane *l : lanes[EAST])
    {
        image[y][0] = '-';
        image[y][1] = '-';
        image[y][2] = '-';
        image[y][3] = '>';

        image[y][w-4] = TrafficLight::colorToString(l->through.getColor())[0];
        image[y][w-3] = '-';
        image[y][w-2] = '-';
        image[y][w-1] = '-';
        y++;
    }

    // Concatenate all the lines together into one string
    std::string retVal;
    for (y = 0; y < h; ++y)
        retVal += image[y] + "\n";

    return retVal;
}
