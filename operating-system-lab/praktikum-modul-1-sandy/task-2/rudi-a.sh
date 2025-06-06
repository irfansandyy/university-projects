#!/bin/bash

if [ ! -e "access.log" ]; then
    echo "access.log not found"
    exit 1
fi

awk -F" " '
BEGIN {
    printf("%-20s %-10s\n", "IP Address", "Status")
    printf("-----------------------------------\n")
} {
    status[$1] += $9
} END {
    for (i in status) {
        printf("%-20s %-10s\n", i, status[i])
    }
    printf("-----------------------------------\n")
}' access.log