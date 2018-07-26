#! /bin/bash

for f in *.txt;
do
	cat "$f" | while read line
	do
		output=$(./search.bash $line)
		
		length=$(echo "$output" | wc -l)
		
		if (( $length > 2 )); then
			echo "$output"
			echo "-------------------------------"
		fi
	done
done
