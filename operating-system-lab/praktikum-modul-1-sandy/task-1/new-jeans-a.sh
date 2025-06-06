#!/bin/bash

if [ ! -e "DataStreamer.csv" ]; then
    echo "DataStreamer.csv not found!"
    exit 1
fi

usernames=$(awk -F, 'NR > 1 && $2 ~ /2/ && $2 !~ /_/ {print $2}' DataStreamer.csv | LC_ALL=C sort)

echo "$usernames"
echo "Total: `echo "$usernames" | wc -l`"