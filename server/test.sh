#!/bin/bash
for i in `seq 1 100000`;
do
	echo "`echo "harsh add 12345 1 1 1"| nc localhost 5000 `"
	sleep 2
done
