#!/bin/bash

counter=0
# generate 3 MB
num_elements=$(( 3 * ((1024*1024)/4) ))
OUTPUT_FILE="./test_data.txt"
MAX_VALUE=999

while [ $counter -lt $num_elements ]; do
  #echo "$((counter % $MAX_VALUE ))" >> $OUTPUT_FILE
  echo "93" >> $OUTPUT_FILE
  counter=$(( $counter + 1 ))
done
