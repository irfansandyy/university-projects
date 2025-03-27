#!/bin/bash

awk -F, '$1 ~ /:/ {print $1}' calender.txt | wc -l