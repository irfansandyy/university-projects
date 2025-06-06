#!/bin/bash

dir=$( dirname -- "$( readlink -f -- "$0"; )"; )

init() {    
    if [ ! -e "$dir/cloud_log.txt" ] || [ ! -e "$dir/cloud_storage" ] || [ ! -e "$dir/cloud_storage/users.txt" ]; then
        echo "No users have been created, register first"
        exit 1
    fi
}

userLogin() {
    read -p "Enter username: " username
    read -s -p "Enter password: " password
    echo
    if [ -z "$username" ] || [ -z "$password" ]; then
        echo "Username or password cannot be empty"
        echo "$currentTime LOGIN: ERROR Failed login attempt on user $username" >> "$dir/cloud_log.txt"
        exit 1
    fi
    if [ $isLoggedIn -eq 1 ]; then
        passwordHash=$(echo -n "$password" | openssl dgst -sha256 | cut -d "=" -f 2)
        grep -q "^$username:$passwordHash" "$dir/cloud_storage/users.txt"
        if [ $? -eq 0 ]; then
            echo "Login successful"
            echo "$currentTime LOGIN: INFO User $username logged in" >> "$dir/cloud_log.txt"
            currentUser="$username"
            ${dir}/init.sh
            return 0
        else
            echo "Invalid username or password"
            echo "$currentTime LOGIN: ERROR Failed login attempt on user $username" >> "$dir/cloud_log.txt"
            exit 1
        fi
    elif [ "$currentUser" = "$username" ]; then
        echo "You are already logged in as $currentUser"
        exit 1
    else 
        echo "Another user ($currentUser) is already logged in, Only one user can be logged in at a time"
        echo "$currentTime LOGIN: ERROR Failed login attempt on user $username" >> "$dir/cloud_log.txt"
        exit 1
    fi
    return 0
}

logout_() {
    if [ -z "$currentUser" ]; then
        echo "No user is logged in"
        return 1
    fi

    echo "Goodbye, $currentUser!"
    echo "$currentTime LOGOUT: INFO User $currentUser logged out" >> "$dir/cloud_log.txt"
    currentUser=""
    return 0
}

# Logged in = 0, Logged Out = 1
checkIfUserLoggedIn() {
    local lastLogin=$(grep "LOGIN: INFO User" "$dir/cloud_log.txt" | tail -n 1)
    local lastLogout=$(grep "LOGOUT: INFO User" "$dir/cloud_log.txt" | tail -n 1)

    if [ -z "$lastLogin" ]; then
        return 1
    elif [ -z "$lastLogout" ]; then
        currentUser=$(echo "$lastLogin" | awk '{print $6}')
        return 0
    else
        loginTime=$(echo "$lastLogin" | awk '{print $1 " " $2}')
        logoutTime=$(echo "$lastLogout" | awk '{print $1 " " $2}')
        
        if [[ "$loginTime" > "$logoutTime" ]]; then
            currentUser=$(echo "$lastLogin" | awk '{print $6}')
            return 0
        fi
    fi
    return 1
}

init
currentTime=$(date +"%y/%m/%d %H:%M:%S")
checkIfUserLoggedIn
isLoggedIn=$?
echo "Current user: $currentUser"
echo "1. Login"
echo "2. Logout"
echo "3. Exit"
read -p "Choose an option: " choice
case $choice in
    1) userLogin ;;
    2) logout_ ;;
    3) echo "exiting program.."; exit 0 ;;
    *) echo "Invalid choice"; exit 1 ;;
esac
exit $?