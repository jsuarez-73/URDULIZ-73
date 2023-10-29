#!/bin/bash

for ((c=1; c<=$LIMIT; c++))
do
	echo -n $((RANDOM%1000));
	echo -n " ";
done
