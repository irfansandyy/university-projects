#!/bin/bash

dir=$( dirname -- "$( readlink -f -- "$0"; )"; )

init() {    
    if [ ! -e "$dir/cloud_log.txt" ] || [ ! -e "$dir/cloud_storage" ] || [ ! -e "$dir/cloud_storage/users.txt" ]; then
        exit 1
    fi
}

archiveImage() {
    local username=$1
    local userDownloads="$dir/cloud_storage/downloads/$username"
    local userArchives="$dir/cloud_storage/archives/$username"
    
    if [ ! -d "$userDownloads" ] || [ -z "$(ls -A "$userDownloads")" ]; then
        echo "$currentTime ARCHIVE: INFO No files to archive for user $username" >> "$dir/cloud_log.txt"
        return 1
    fi
    
    mkdir -p "$userArchives"
    local archiveName="archive_$currentDate.zip"
    local tempDir=$(mktemp -d)
    
    find "$userDownloads" -name "*.zip" -type f -exec cp {} "$tempDir/" \;
    
    cd "$tempDir"
    find "$tempDir" -maxdepth 1 -type f -name "*.zip" -exec sh -c '
    for file; do
        zipdir="${file%.zip}"
        mkdir -p "$zipdir"
        unzip -q "$file" -d "$zipdir"
        rm "$file"
    done' sh {} +
    zip -q -r "$userArchives/$archiveName" .
    cd "$dir"
    
    find "$userDownloads" -name "*.zip" -type f -delete
    echo "$currentTime ARCHIVE: INFO Successfully created archive for user $username" >> "$dir/cloud_log.txt"
    rm -rf "$tempDir"
}

init
currentTime=$(date +"%y/%m/%d %H:%M:%S")
currentDate=$(date +"%H-%d-%m-%Y")
mkdir -p "$dir/cloud_storage/archives"
users=$(find "$dir/cloud_storage/downloads" -maxdepth 1 -type d | grep -v "^$dir/cloud_storage/downloads$" | xargs -n1 basename)

if [ -z "$users" ]; then
    echo "${currentTime} ARCHIVE: INFO No users found for archiving" >> "$dir/cloud_log.txt"
    exit 1
fi

for username in $users; do
    archiveImage "$username"
done