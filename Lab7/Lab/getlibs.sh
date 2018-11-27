#!/bin/bash

lddlist=$(ls /usr/bin | awk 'NR%101==404937201%101')

for cmd in $lddlist;
do
     echo $cmd
     ldd $(which $cmd)
done
