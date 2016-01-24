/* 
 * File:   Ticks.hh
 * Author: ehein6
 *
 * Created on January 28, 2015, 2:56 PM
 */

#ifndef TICKS_HH
#define	TICKS_HH

#include <inttypes.h>


typedef uint64_t Tick;

#define TICKS_PER_SECOND 100
/**
 * Converts a value from seconds to ticks
 */
Tick secondsToTicks(float s);
/**
 * Converts a value from ticks to seconds
 */
float ticksToSeconds(Tick t);

#endif	/* TICKS_HH */

