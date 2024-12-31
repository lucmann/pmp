#!/bin/bash
# Start 4 instances of glmark2 in the background
for i in {1..4}; do
    eval "glmark2 -b build >$i.log 2>&1 & PID_$i=\$!"
    echo "Started glmark2 with PID $! and logging to $i.log"
done

wait $PID_1 $PID_2 $PID_3 $PID_4

for i in {1..4}; do
    var="PID_$i"
    # bash does not interpret nested variable references
    echo "Renaming $i.log to glmark2.${!var}.log"
    mv "$i.log" "glmark2.${!var}.log"
done

