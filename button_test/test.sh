#!/bin/bash

while true; do amixer set Master $(rec -n stat trim 0 .5 2>&1 | awk '/^Maximum amplitude/ { print $3 < .15 ? 80 : 0 }'); done
