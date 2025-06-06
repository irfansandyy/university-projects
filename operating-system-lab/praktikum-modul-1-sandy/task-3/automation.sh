#!/bin/bash

dir=$( dirname -- "$( readlink -f -- "$0"; )"; )

init() {    
    if [ ! -e "$dir/cloud_log.txt" ] || [ ! -e "$dir/cloud_storage" ] || [ ! -e "$dir/cloud_storage/users.txt" ]; then
        exit 1
    fi
}

whenLoggedIn() {
    echo "$currentTime STATUS: INFO $currentUser is logged in" >> "$dir/cloud_log.txt"
    echo "SHELL=/bin/bash
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

*/2 * * * * /bin/bash $dir/automation.sh >> $dir/cloud_log.txt
1-59/10 * * * * /bin/bash $dir/download.sh >> $dir/cloud_log.txt
3 */2 * * * /bin/bash $dir/archive.sh >> $dir/cloud_log.txt
" > /tmp/tempCrontab
    crontab /tmp/tempCrontab
    rm /tmp/tempCrontab
    exit 0
}

whenLoggedOut() {
    echo "$currentTime STATUS: ERROR No user is logged in" >> "$dir/cloud_log.txt"
    echo "SHELL=/bin/bash
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

*/2 * * * * /bin/bash $dir/automation.sh >> $dir/cloud_log.txt
" > /tmp/tempCrontab
    crontab /tmp/tempCrontab
    rm /tmp/tempCrontab
    exit 1
}

checkIfUserLoggedIn() {
    local lastLogin=$(grep "LOGIN: INFO User" "$dir/cloud_log.txt" | tail -n 1)
    local lastLogout=$(grep "LOGOUT: INFO User" "$dir/cloud_log.txt" | tail -n 1)

    if [ -z "$lastLogin" ]; then
        whenLoggedOut
    elif [ -z "$lastLogout" ]; then
        currentUser=$(echo "$lastLogin" | awk '{print $6}')
        whenLoggedIn
    else
        loginTime=$(echo "$lastLogin" | awk '{print $1 " " $2}')
        logoutTime=$(echo "$lastLogout" | awk '{print $1 " " $2}')
        
        if [[ "$loginTime" > "$logoutTime" ]]; then
            currentUser=$(echo "$lastLogin" | awk '{print $6}')
            whenLoggedIn
        else 
            whenLoggedOut
        fi
    fi
    return 1
}

init
currentTime=$(date +"%y/%m/%d %H:%M:%S")
checkIfUserLoggedIn
exit 1