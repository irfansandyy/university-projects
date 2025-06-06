#!/bin/bash

if [! -f "DataStreamer.csv"]; then
    echo "DataStreamer.csv not found!"
    exit 1
fi

platformCountTime=$(awk -F, '
    NR > 1 {gsub(/\r/, "", $7); user[$7] += 1;time[$7] += $4}
    END {
        for (i in time) {
            print i "," user[i] "," time[i]
        }
    }' DataStreamer.csv | sort -t, -nrk2)

mostPlatformLoyalty=$(awk -F, '{loyalty[$1] = $3/$2} END{for (i in loyalty) {print i "," loyalty[i]}}' <<< "$platformCountTime" | sort -t, -nrk1 | head -n 1)

printf "%-11s %-7s %-10s\n" "Platform" "Users" "Time (seconds)"
echo "--------------------------------------"
awk -F, '{printf "%-11s %-7s %-10s\n", $1, $2, $3}' <<< "$platformCountTime"
echo "--------------------------------------"
awk -F, 'NR == 1 {printf "Most popular platform: %s (%s Users)\n", $1, $2}' <<< "$platformCountTime"
echo "$platformCountTime" | sort -t, -nrk3 | awk -F, 'NR == 1 {printf "Most stream time: %s (%s Seconds)\n", $1, $3}'
awk -F, '{printf "Most loyal platform: %s (%s Seconds/User)\n", $1, $2}' <<< "$mostPlatformLoyalty"