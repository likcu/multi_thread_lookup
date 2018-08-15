#!/bin/bash

counter=0
# generate 4 MB
num_elements=$(( 4 * ((1024*1024)/4) ))
OUTPUT_FILE="./test_data.txt"
MAX_VALUE=50

while [ $counter -lt $num_elements ]; do
  echo "$((counter % $MAX_VALUE ))" >> $OUTPUT_FILE
  counter=$(( $counter + 1 ))
done
