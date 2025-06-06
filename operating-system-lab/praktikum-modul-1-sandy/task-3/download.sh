#!/bin/bash

dir=$( dirname -- "$( readlink -f -- "$0"; )"; )
source ~/.bashrc

init() {    
    if [ ! -e "$dir/cloud_log.txt" ] || [ ! -e "$dir/cloud_storage" ] || [ ! -e "$dir/cloud_storage/users.txt" ]; then
        exit 1
    fi
}

download() {
    userDir="$dir/cloud_storage/downloads/$username"
    mkdir -p "$userDir"
    
    timestamp=$(date +%H-%M_%d-%m-%Y)
    zipName="$timestamp.zip"
    tempDir=$(mktemp -d)
    numImages=5

    imageUrls=$(curl -s "https://www.googleapis.com/customsearch/v1?key=$GOOGLE_API_KEY&cx=$GOOGLE_CSE_ID&q=nature+images&searchType=image&fileType=jpg&safe=active&num=10" | jq -r '.items[] | .link')

    readarray -t downloadLinks <<< "$imageUrls"
    urlCount=${#downloadLinks[@]}

    if [[ "$urlCount" -eq 0 ]]; then
        echo "$currentTime DOWNLOAD: ERROR No image URLs found" >> "$dir/cloud_log.txt"
        exit 1
    fi

    shuffledLinks=($(shuf -e "${downloadLinks[@]}"))
    for num in $(seq 1 $numImages); do
        imageUrl="${shuffledLinks[$num - 1]}"
        curl -s -L --fail "$imageUrl" -o "$tempDir/${timestamp}_${num}.jpg" || {
            echo "$currentTime DOWNLOAD: ERROR Failed to download $imageUrl" >> "$dir/cloud_log.txt"
        }
    done

    cd "$tempDir"
    zip -q "$userDir/$zipName" ./*
    cd "$dir"
    rm -rf "$tempDir"
    
    echo "$currentTime DOWNLOAD: INFO Successfully downloaded images for $username as $zipName" >> "$dir/cloud_log.txt"
}

init
currentTime=$(date +"%y/%m/%d %H:%M:%S")
lastStatus=$(grep "STATUS: INFO" "$dir/cloud_log.txt" | tail -n 1)
username=$(echo "$lastStatus" | awk '{print $5}')
download