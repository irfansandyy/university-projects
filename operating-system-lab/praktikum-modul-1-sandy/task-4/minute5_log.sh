#!/bin/bash

userpath="/home/$(whoami)"

if [ ! -e "$userpath/metrics" ]; then
    mkdir -p "$userpath/metrics"
    chmod 700 "$userpath/metrics"
fi

usersize=$(du -s "$userpath" | awk '{printf "%dM", ($1/1024)}')
timestamp=$(date +"%Y%m%d%H%M%S")

metrics=$(free -m | awk -v userpath="$userpath" -v usersize="$usersize" '
BEGIN {
    print "mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size"
} NR == 2 {
    printf "%s,%s,%s,%s,%s,%s,", $2, $3, $4, $5, $6, $7
} NR == 3 {
    printf "%s,%s,%s,%s/,%s\n", $2, $3, $4, userpath, usersize
}')

metricsFile="$userpath/metrics/metrics_$timestamp.log"

echo "$metrics" > "$metricsFile"
chmod 700 "$metricsFile"