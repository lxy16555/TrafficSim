
/* 
 * File:   RandomVar.hh
 * Author: theak
 *
 * Created on January 26, 2015, 4:09 PM
 */
#include <math.h>
#include <stdlib.h>

#ifndef RANDOMVAR_HH
#define	RANDOMVAR_HH

/**
 * Implements random variable generation for the simulation
 */
class RandomVar {
public:
    /**
     * Seeds the random number generator
     */
    static void seed(int seed);
    /**
     * Generates an inter-arrival time according to an exponential distribution
     * @param lambda parameter for exponential distribution
     */
    static double interArr (double lambda);
    /**
     * Generates a uniformly distributed random number for initializing traffic light init times
     */
    static double initSignal();
    /**
     * Generates a uniformly distributed random double in the range (0, max)
     * @param top end of random range
     */
    static double getDouble(double max);
    /**
     * Generates a uniformly distributed random integer in the range (0, max)
     * @param top end of random range
     */
    static int getInt(int max);
private:

};

#endif	/* RANDOMVAR_HH */
