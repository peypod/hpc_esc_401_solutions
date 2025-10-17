#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

in_num="$1"


if ! [[ "$in_num" =~ ^-?[0-9]+$ ]]; then
    echo "ERROR: The given input is not a number: $in_num"
    exit 1
fi

if [ "$in_num" -le 0 ]; then
    echo "ERROR: The given input is not a positive integer: $in_num"
    exit 1
fi



factors=$(factor "$in_num")
count=$(echo "$factors" | wc -w)

if [ "$count" -eq 2 ]; then
    echo "$in_num is prime"
else
    echo "$in_num is composite"
fi
