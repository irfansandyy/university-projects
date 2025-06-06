#!/bin/bash

if [ ! -e "DataStreamer.csv" ]; then
    echo "DataStreamer.csv not found!"
    exit 1
elif [ ! -e "AlbumDetails.csv" ]; then
    echo "AlbumDetails.csv not found!"
    exit 1
fi

topSong=$(awk -F, 'NR > 1 && $2 ~ /[0-9]/ && $2 !~ /_/ {print ","$3}' DataStreamer.csv | sort | uniq -c | sort -nr | head -n 1)

topSong=$topSong","$(awk -F, -v name="`awk -F, '{print $2}' <<< "$topSong"`" 'NR > 1 && $2 == name {print $1 "," $3}' AlbumDetails.csv)

echo "Most popular song: `awk -F, '{print $2}' <<< "$topSong"`"
echo "Album: `awk -F, '{print $3}' <<< "$topSong"`"
echo "Year: `awk -F, '{print $4}' <<< "$topSong"`"