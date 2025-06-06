#!/bin/bash

userpath="/home/$(whoami)"

if [ ! -e "$userpath/metrics" ]; then
    mkdir -p "$userpath/metrics"
    chmod 700 "$userpath/metrics"
fi

computerUptime=$(uptime | awk -F" " '{gsub(/,/, "", $3);printf "%s  %s  %s", $1, $2, $3}')
computerLoadAvg=$(cat /proc/loadavg | awk -F" " '{print $1 "," $2 "," $3}')
timestamp=$(date +"%Y%m%d%H")

uptimeFile="$userpath/metrics/uptime_$timestamp.log"

printf "uptime,load_avg_1min,load_avg_5min,load_avg_15min\n%s,%s\n" "$computerUptime" "$computerLoadAvg" > "$uptimeFile"
chmod 700 "$uptimeFile"