#!/bin/bash

dir=$( dirname -- "$( readlink -f -- "$0"; )"; )

    echo "SHELL=/bin/bash
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

*/2 * * * * /bin/bash $dir/automation.sh >> $dir/cloud_log.txt
" > /tmp/tempCrontab
    crontab /tmp/tempCrontab
    rm /tmp/tempCrontab
    