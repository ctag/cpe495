#!/bin/bash

SAMPLE=/dev/shm/tmp_rec.wav
STATE=0

# End the script, not the recording
trap 'echo "ctrl c caught, exiting"; exit' INT

while [ 1 ]
do
	#arecord -d 1 $SAMPLE
	rec -c 1 $SAMPLE trim 0 0.05 > /dev/null 2> /dev/null

	if [ $STATE -eq 0 ]; then
		sox -t .wav $SAMPLE -n stat 2>&1 | grep "Mean    delta" | cut -d ':' -f 2 | \
		awk '{ printf ($1); if ($1 < 0.001) { exit 1; } else { exit 0; } };'
		STATE=$?
		if [ $STATE -eq 1 ]; then
			xdotool key Right
			#xdotool key x
		fi
	else
		sox -t .wav $SAMPLE -n stat 2>&1 | grep "Mean    delta" | cut -d ':' -f 2 | \
		awk '{ printf ($1); if ($1 < 0.001) { exit 1; } else { exit 0; } };'
		STATE=$?
	fi	

	echo $INFO
done
