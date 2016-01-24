#!/bin/bash

saveOutput()
{
	mv results.csv $1.csv
}

# Stop on all errors
set -e

NUM_TRIALS=10

for i in `seq 1 $NUM_TRIALS`;
do 
	./trafficSim async
	saveOutput "async-$i"
done


for i in `seq 1 $NUM_TRIALS`;
do 
	for t in 0 5 10 15 20;
	do
		./trafficSim sync $t
		saveOutput "sync$t-$i"
	done 
done

