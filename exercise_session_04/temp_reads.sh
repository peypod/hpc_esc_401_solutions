#!/bin/bash

output_file="out.txt"
 > "$output_file"


total_temp=0
count=0

for file in measured/measurement*.txt; do

	readings=$(grep -E "^Temperature:.*" "$file")
	temps=$(grep -P "/d*/./d*" "$readings")

	echo "$readings" >> "$output_file"

	while read -r r; do
        
		temp_val=$(echo "$r" | grep -oE "[0-9]+\.[0-9]+")
		temp_val=$(echo "$temp_val" | head -n1)

		# echo "$temp_val"

		if [ -n "$temp_val" ]; then
	
			total_temp=$(echo "$total_temp + $temp_val" | bc)
            		count=$((count + 1))

		fi
	done <<< "$readings"
done

avg=$(echo "scale=2; $total_temp / $count" | bc)
echo "Average Temperature: $avg"
