/* 
 * File:   RandomVar.cc
 * Author: theak
 * 
 * Created on January 26, 2015, 4:09 PM
 */

#include "RandomVar.hh"

void RandomVar::seed(int seed) {
    // For randomization use a time based seed? seed = time(NULL))
    srand(seed);
}

double RandomVar::interArr (double lambda){
    if(lambda == -1){
        return 100000;
    }
    else{
        // lambda unit 1/sec
         int rn = rand()%(RAND_MAX-1) +1;
         double urn = (double)rn/(double)(RAND_MAX);
         double interArr = -log(urn)/lambda;
         return interArr;
        //double mu = 1/lambda;
        //return mu;
    }
}

double RandomVar::initSignal(){
    return getDouble(200);
}

double RandomVar::getDouble(double max){
    int rn2 = rand();
    double urn2 = (double)rn2/(double)(RAND_MAX);
    return urn2*max;
}

int RandomVar::getInt(int max){
    return rand() % max;
}
