#!/bin/bash

if [ ! -e "DataStreamer.csv" ]; then
    echo "DataStreamer.csv not found!"
    exit 1
fi

topSong=$(awk -F, 'NR > 1 && $2 ~ /[0-9]/ && $2 !~ /_/ {print $3}' DataStreamer.csv | sort | uniq -c | sort -nr | head -n 1)

echo "Most popular song: `awk '{print $2}' <<< "$topSong"`"
echo "Number of users: `awk '{print $1}' <<< "$topSong"`"

if [ `awk '{print $1}' <<< "$topSong"` -ge 24 ]; then
    echo "Cool, Minji! You're great <3!"
else
    echo "Sorry, Minji, the total streaming is not as expected :("
fi