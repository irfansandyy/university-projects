#!/bin/bash

dir=$( dirname -- "$( readlink -f -- "$0"; )"; )

init() {    
    if [ ! -e "$dir/cloud_log.txt" ]; then
        touch $dir/cloud_log.txt
    fi

    if [ ! -e "$dir/cloud_storage" ]; then
        mkdir -p $dir/cloud_storage
    fi

    if [ ! -e "$dir/cloud_storage/users.txt" ]; then 
        touch "$dir/cloud_storage/users.txt"
    fi
}

checkPassword() {
    local username=$1
    local password=$2
    
    if [ ${#password} -lt 8 ]; then
        echo "Password must be at least 8 characters long"
        echo "$currentTime REGISTER: ERROR Password is not 8 characters long" >> "$dir/cloud_log.txt"
        return 1
    elif ! [[ $password =~ [A-Z] ]]; then
        echo "Password must contain at least one uppercase letter"
        echo "$currentTime REGISTER: ERROR Password does not contain a single uppercase letter" >> "$dir/cloud_log.txt"
        return 1
    elif ! [[ $password =~ [0-9] ]]; then
        echo "Password must contain at least one number"
        echo "$currentTime REGISTER: ERROR Password does not contain a single number" >> "$dir/cloud_log.txt"
        return 1
    elif ! [[ $password =~ [[:punct:]] ]]; then
        echo "Password must contain at least one special character"
        echo "$currentTime REGISTER: ERROR Password does not contain a single special character" >> "$dir/cloud_log.txt"
        return 1
    elif [ "$password" = "$username" ]; then
        echo "Password cannot be the same as username"
        echo "$currentTime REGISTER: ERROR Password is the same as username" >> "$dir/cloud_log.txt"
        return 1
    elif [[ $password =~ [cC][lL][oO][uU][dD] ]] || [[ $password =~ [sS][tT][oO][rR][aA][gG][eE] ]]; then
        echo "Password cannot contain the words 'cloud' or 'storage'"
        echo "$currentTime REGISTER: ERROR Password contains 'cloud' or 'storage'" >> "$dir/cloud_log.txt"
        return 1
    fi
    return 0
}

checkUsername() {
    local username=$1
    if [ ! -s "$dir/cloud_storage/users.txt" ]; then
        return 0
    fi

    if [[ $username =~ [[:space:]/\\] ]]; then
        echo "Username cannot contain whitespaces, forward or backward slash"
        echo "$currentTime REGISTER: ERROR Username contained whitespaces, forward or backward slash" >> "$dir/cloud_log.txt"
        return 1
    fi

    grep -q "^${username}:" "$dir/cloud_storage/users.txt"

    if [ $? -eq 0 ]; then
        echo "User already exists"
        echo "$currentTime REGISTER: ERROR User already exists" >> "$dir/cloud_log.txt"
        return 1
    fi
    return 0
}

init
read -p "Enter username: " username
read -s -p "Enter password: " password
echo

if [ -z "$username" ] || [ -z "$password" ]; then
    echo "Username and password cannot be empty"
    exit 1
fi

currentTime=$(date +"%y/%m/%d %H:%M:%S")

if checkPassword "$username" "$password" && checkUsername "$username"; then
    echo "Successfully registered"
    echo "$currentTime REGISTER: INFO User registered successfully" >> "$dir/cloud_log.txt"
    password=$(echo -n "$password" | openssl dgst -sha256 | cut -d "=" -f 2)
    echo "$username:$password" >> "$dir/cloud_storage/users.txt"
fi