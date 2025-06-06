#!/bin/bash

if [ ! -e "access.log" ]; then
    echo "access.log not found"
    exit 1
elif [ ! -e "peminjaman_computer.csv" ]; then
    echo "peminjaman_computer.csv not found"
    exit 1
fi

awk -F" " '
BEGIN {
    andi = 0; budi = 0; caca = 0;

    getline line < "peminjaman_computer.csv";
    while ((getline line < "peminjaman_computer.csv") > 0) {
        split(line, lines, ",");
        date = lines[1];
        computer = lines[2];
        user = lines[3];
        map[date "," computer] = user;
    }
    close("peminjaman_computer.csv");
}

{
    if ($9 == 500) {
        split($1, ips, ".");
        computer = ips[4];
        
        date = $4;
        gsub(/[\[\]]/, "", date);
        split(date, dates, "/|:");
        
        months["Jan"] = "01"; months["Feb"] = "02"; months["Mar"] = "03";
        months["Apr"] = "04"; months["May"] = "05"; months["Jun"] = "06";
        months["Jul"] = "07"; months["Aug"] = "08"; months["Sep"] = "09";
        months["Oct"] = "10"; months["Nov"] = "11"; months["Dec"] = "12";
        
        formattedDate = months[dates[2]] "/" dates[1] "/" dates[3];
        lookupKey = formattedDate "," computer;
        user = map[lookupKey];
        
        if (user == "Andi") andi++;
        else if (user == "Budi") budi++;
        else if (user == "Caca") caca++;
    }
}

END {
    printf "%-5s %-7s\n", "Name", "Count";
    printf "--------------------\n"
    printf "%-5s %-7s\n", "Andi", andi;
    printf "%-5s %-7s\n", "Budi", budi;
    printf "%-5s %-7s\n", "Caca", caca;
    printf "--------------------\n";
    max = andi
    if (budi+0 > max+0) {
        max = budi;
        print "Budi berhak mendapatkan hadiah";
    } else if (caca+0 > max+0) {
        max = caca;
        print "Caca berhak mendapatkan hadiah";
    } else {
        print "Andi berhak mendapatkan hadiah";
    }
}' access.log