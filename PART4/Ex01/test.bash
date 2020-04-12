#!/bin/bash
d=$(date +'%G/%m/%d %H:%M:%S')
h=$(hostname -f)
w=$(whoami)
p=$(pwd)
l=$(wc -l $2)
echo -e "date: ${d} wait: ${1}\nhost: ${h} user: ${w}"
echo -e "path: ${p}\nlines in $2: ${l}"
sleep $1
date +'%G/%m/%d %H:%M:%S'
