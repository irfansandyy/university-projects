#!/bin/bash

userpath="/home/$(whoami)"

if [ ! -e "$userpath/metrics" ]; then
    exit 1
fi

timestamp=$(date +"%Y%m%d13" -d "yesterday")
deletedFiles=$(find "$userpath/metrics" -type f -name "metrics_agg_*.log")

for file in $deletedFiles; do
    fileDate=$(echo "$file" | cut -d'_' -f 3 | cut -d'.' -f 1)
    if [ "$fileDate" -lt "$timestamp" ]; then
        rm -f "$file"
    fi
done