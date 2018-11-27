#!/bin/bash

lddlist=$(ls /usr/bin | awk 'NR%101==404937201%101')
dynamiclibs=""
for cmd in $lddlist;
do
    dynamiclibs="$dynamiclibs"$(ldd $(which $cmd))$(echo)
done

echo "$dynamiclibs" | grep '.so' | sed 's/(.*//' | sort -u
