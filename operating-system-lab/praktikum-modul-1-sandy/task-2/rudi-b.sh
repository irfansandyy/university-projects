#!/bin/bash

if [ ! -e "access.log" ]; then
    echo "access.log not found"
    exit 1
elif [ ! -e "peminjaman_computer.csv" ]; then
    echo "peminjaman_computer.csv not found"
    exit 1
fi

read -p "Enter the date to search (MM/DD/YYYY): " date
read -p "Enter the IP address to search (192.168.1.X): " ipAddress

computer=${ipAddress:0-1}
computer=$(tail +2 peminjaman_computer.csv | grep "$date" | cut -d "," -f 2-3 | grep "$computer")

username=$(echo "$computer" | cut -d "," -f 2)

if [ -z "$computer" ]; then
    echo "Data yang kamu cari tidak ada"
    exit 1
else
    echo "Pengguna saat itu adalah $username"
    echo "Log Aktivitas $username"
fi

errorlog=$(cat access.log | grep "$ipAddress" | grep -F "[$day`echo "$date" | cut -d"/" -f 2`")

errorlog=$(echo "$errorlog" | awk -F" " '{
    gsub(/[\[\]"]/, "");
    print "[" $4 "]: " $6 " - " $7 " - " $9
}')

date=$(echo "$date" | awk -F"/" '{print $1 $2 $3}')
currentTime=$(date +%H%M%S)

mkdir -p "backup"
touch $PWD/backup/${username}_${date}_${currentTime}.log

echo "$errorlog" > "${PWD}/backup/${username}_${date}_${currentTime}.log"