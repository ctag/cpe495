#!/bin/bash

# This shell script reads the provided serial device
# and whenever something is printed it will
# generate a "Right" button press

while read line
do
	echo $line
	xdotool key Right
done < /dev/ttyUSB0
