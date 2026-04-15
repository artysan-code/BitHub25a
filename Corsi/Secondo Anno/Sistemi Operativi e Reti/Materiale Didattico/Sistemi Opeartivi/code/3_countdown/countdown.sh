#!/bin/bash

# Check if a parameter is given
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <starting_number>"
    exit 1
fi

START_NUM=$1

for i in $(seq $START_NUM -1 1); do
    echo $i
    sleep $((RANDOM % 3))
done
