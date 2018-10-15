#!/bin/bash

rm SAMPLE SAMPLE2

IFS=' ,'

cat TEST.htm | grep -o '<td>\(..*\)</td>' > SAMPLE

state=true

dictHawaii=""

while read p; do
    if [ "$state" = false ] ; then
        dictHawaii="$dictHawaii $p"
	state=true
    else
	state=false
    fi
    
done <SAMPLE

dictHawaii=$(echo "$dictHawaii" | tr A-Z a-z | tr '`' "'")

dictHawaii=$(echo "$dictHawaii" | sed 's/<td>//g' | sed 's/<\/td>//g' | sed 's/<u>//g' | sed 's/<\/u>//g')

for word in ${dictHawaii[@]}
do
    echo $word >> SAMPLE2
done


    

cat SAMPLE2 | tr -c "pk'mnwlhaeiou" '[\n*]' | sort -u > SAMPLE

cat SAMPLE
