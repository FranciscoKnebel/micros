#! /bin/sh
### BEGIN INIT INFO
# Provides:          eng10032lab05_1
# Required-Start:    
# Should-Start:      
# Required-Stop:     
# Default-Start:     S
# Default-Stop:
# Short-Description: Configures GPIO and interrupts for Lab 05.
# Description:       Configures GPIO and interrupts for Lab 05.
### END INIT INFO

case "$1" in
    start|restart|force-reload)
   	# IO4 = gpio6
	if [ ! -d /sys/class/gpio/gpio6 ] ; then
	    echo -n "6" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio6/direction
	chgrp gpio /sys/class/gpio/gpio6/value
	chmod g+r /sys/class/gpio/gpio6/value
	chgrp gpio /sys/class/gpio/gpio6/edge
	chmod g+rw /sys/class/gpio/gpio6/edge

	# gpio36 = 1 => IO4=in	
	if [ ! -d /sys/class/gpio/gpio36 ] ; then
	    echo -n "36" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio36/direction
	echo -n "1" > /sys/class/gpio/gpio36/value

	# gpio37 = 0 => pull-down
	if [ ! -d /sys/class/gpio/gpio37 ] ; then
	    echo -n "37" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio37/direction
	echo -n "0" > /sys/class/gpio/gpio37/value
	

	;;
    stop)
    	echo -n "in" > /sys/class/gpio/gpio37/direction
    	echo -n "37" > /sys/class/gpio/unexport
	echo -n "36" > /sys/class/gpio/unexport
	echo -n "6" > /sys/class/gpio/unexport
	;;
    status)
    	ls -d /sys/class/gpio/gpio*
	;;
    *)
	echo -n "Usage: $0 " 
	echo "{start|stop|restart|force-reload|status}"
	exit 1
	;;
esac

exit 0
