#!/bin/bash

# Set the directory
dir="output_greedyLT2"

# Create a new output file
output_file="LT2"
touch $output_file

# Go through each file in the directory
for file in $dir/*; do
    # Extract the file name without the extension
    file_name=$(basename "$file" .salida)

    # Extract the Execution time and SIZE
    execution_time=$(grep -m 1 "Execution time" "$file" | awk '{print $3}')
    size=$(grep -m 1 "SIZE" "$file" | awk '{print $2}')

    # Save the extracted data to the output file
    echo "${file_name}.salida" >> $output_file
    echo "SIZE $size" >> $output_file
    echo "Execution time: $execution_time ms" >> $output_file
    echo "" >> $output_file
done
