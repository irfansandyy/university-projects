#!/bin/bash

userpath="/home/$(whoami)"

if [ ! -e "$userpath/metrics" ]; then
    exit 1
fi

timestamp=$(date +"%Y%m%d%H")
logFiles=$(find "$userpath/metrics" -type f -name "metrics_*.log" ! -name "metrics_agg_*.log")

if [ -z "$logFiles" ]; then
    exit 1
fi

for file in $logFiles; do
    awk -F, 'NR == 2 {gsub(/M/, "", $11); print $1 "," $2 "," $3 "," $4 "," $5 "," $6 "," $7 "," $8 "," $9 "," $10 "," $11}' "$file" >> /tmp/metrics_agg_temp.log
done

awk -F, -v userpath="$userpath" '
function find_min(arr, n) {
    min_val = arr[1]
    for (i = 2; i <= n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i]
        }
    }
    return min_val
}

function find_max(arr, n) {
    max_val = arr[1]
    for (i = 2; i <= n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i]
        }
    }
    return max_val
}

function average(arr, n) {
    sum = 0
    for (i = 1; i <= n; i++) {
        sum += arr[i]
    }
    return sum / n
}

{
    mem_total[NR] = $1
    mem_used[NR] = $2
    mem_free[NR] = $3
    mem_shared[NR] = $4
    mem_buff[NR] = $5
    mem_available[NR] = $6
    swap_total[NR] = $7
    swap_used[NR] = $8
    swap_free[NR] = $9
    path_size[NR] = $11
} END {
    print "type,mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size"

    printf "minimum,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s/,%sM\n", find_min(mem_total, NR), find_min(mem_used, NR), find_min(mem_free, NR), find_min(mem_shared, NR), find_min(mem_buff, NR), find_min(mem_available, NR), find_min(swap_total, NR), find_min(swap_used, NR), find_min(swap_free, NR), userpath, find_min(path_size, NR)

    printf "maximum,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s/,%sM\n", find_max(mem_total, NR), find_max(mem_used, NR), find_max(mem_free, NR), find_max(mem_shared, NR), find_max(mem_buff, NR), find_max(mem_available, NR), find_max(swap_total, NR), find_max(swap_used, NR), find_max(swap_free, NR), userpath, find_max(path_size, NR)

    printf "average,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s/,%sM\n", average(mem_total, NR), average(mem_used, NR), average(mem_free, NR), average(mem_shared, NR), average(mem_buff, NR), average(mem_available, NR), average(swap_total, NR), average(swap_used, NR), average(swap_free, NR), userpath, average(path_size, NR)
}' /tmp/metrics_agg_temp.log > "$userpath/metrics/metrics_agg_$timestamp.log"

rm /tmp/metrics_agg_temp.log
chmod 700 "$userpath/metrics/metrics_agg_$timestamp.log"

for file in $logFiles; do
    rm "$file"
done