#!/bin/bash

# Check if the argument is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <start_index>"
    exit 1
fi

# Read the start index
x=$1

# Run the program 5 times and append the output
for ((i=x; i<x+5; i++)); do
    echo "Running iteration $i"
    g++ BottomLeftFillSolution.cpp
    ./a.out > "out${i}.txt"
    sleep (1)
done
