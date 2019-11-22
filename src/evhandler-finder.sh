# JMIRY
#!/bin/bash

node=$1
# get sysfs path
syspath=$(udevadm info -q path ${node})
# subsequent path from '/hidraw' is unnecessary, slice it away
syspath=${syspath%%/hidraw*}
# query device specific info from kernel file
info=$(cat /proc/bus/input/devices | grep -A 2 $syspath)
# get event handler
event=$(expr match "$info" '.*\(event[0-9]*\).*')

echo $event
