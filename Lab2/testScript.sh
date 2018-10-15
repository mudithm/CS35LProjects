#!/bin/bash
rm SAMPLE SAMPLE2
# add the comma to the field separators list
IFS=' ,'

# reduce the file to only the items between <td> and </td>
cat TEST.htm | egrep -o '<td>(..*)</td>' > SAMPLE

# declares a boolean variable to keep track of state
state=true

# declares a string to contain the text of the file
dictHawaii=""

# remove every other line of the code, leaving only the
# hawaiian words

while read p; do
    if [ "$state" = false ] ; then
        dictHawaii="$dictHawaii $p"
	state=true
    else
	state=false
    fi
    
done <SAMPLE


# replace ascii grave accent with apostrophe
dictHawaii=$(echo "$dictHawaii" | tr A-Z a-z | tr '`' "'")

# move remaining html tags
dictHawaii=$(echo "$dictHawaii" | sed 's/<td>//g' | sed 's/<\/td>//g' | sed 's/<u>//g' | sed 's/<\/u>//g')

# add separated words to a new file
for word in ${dictHawaii[@]}
do
    echo $word >> SAMPLE2
done

# remove non-Hawaiian words and sort the words in the file
cat SAMPLE2 | egrep -o "^[pk'mnwlhaeiou]*$" | sort -u > SAMPLE


cat SAMPLE
