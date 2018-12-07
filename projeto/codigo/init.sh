## IO2  = INPUT S_ELB1
## IO3  = INPUT S_ELB2
## IO7  = OUTPUT H ENABLE
## IO5  = PWM3 
## IO10 = SPI #SS
## IO11 = SPI MOSI
## IO12 = SPI MISO
## IO13 = SPI SCLK

######### estão faltando S_SH1, S_SH2 e CNT_EN

case "$1" in
    start|restart|force-reload)
    ### GPIO SENSORS
    ## IO2 = INPUT S_ELB1
	if [ ! -d /sys/class/gpio/gpio13 ] ; then
	    echo -n "13" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio13/direction
	chgrp trab /sys/class/gpio/gpio13/value
	chmod g+r /sys/class/gpio/gpio13/value
	# gpio38 = 1  = out
	if [ ! -d /sys/class/gpio/gpio34 ] ; then
	    echo -n "34" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio34/direction
	echo -n "1" > /sys/class/gpio/gpio34/value
	# gpio35 = 0 = out = pull-down resistor
	if [ ! -d /sys/class/gpio/gpio35 ] ; then
	    echo -n "35" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio35/direction
	echo -n "0" > /sys/class/gpio/gpio35/value
	# gpio77 = 0
	if [ ! -d /sys/class/gpio/gpio77 ] ; then
	    echo -n "77" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio77/value

	## IO3 = INPUT S_ELB2
    if [ ! -d /sys/class/gpio/gpio14 ] ; then
	    echo -n "14" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio14/direction
	chgrp trab /sys/class/gpio/gpio14/value
	chmod g+r /sys/class/gpio/gpio14/value
		# gpio16 = 1 = out
	if [ ! -d /sys/class/gpio/gpio16 ] ; then
	    echo -n "16" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio16/direction
	echo -n "1" > /sys/class/gpio/gpio16/value
	# gpio17 = 0 = out = pull-down resistor
	if [ ! -d /sys/class/gpio/gpio17 ] ; then
	    echo -n "17" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio17/direction
	echo -n "0" > /sys/class/gpio/gpio17/value
	# gpio76 = 0
	if [ ! -d /sys/class/gpio/gpio76 ] ; then
	    echo -n "76" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio76/value
    # gpio64 = 0
	if [ ! -d /sys/class/gpio/gpio64 ] ; then
	    echo -n "64" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio64/value
    
    ### H ENABLE
    ## IO7 = OUTPUT H ENABLE
    if [ ! -d /sys/class/gpio/gpio38 ] ; then
	    echo -n "38" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio38/direction
	echo -n "0" > /sys/class/gpio/gpio38/value
	chgrp trab /sys/class/gpio/gpio38/value
	chmod g+r /sys/class/gpio/gpio38/value
	# gpio39 = in = no pull-up nor pull-down resistor
	if [ ! -d /sys/class/gpio/gpio39 ] ; then
	    echo -n "39" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio39/direction

    ### PWM 
    ## IO5 = PWM3 
	if [ ! -d /sys/class/pwm/pwmchip0/pwm3 ] ; then
	    echo -n "3" > /sys/class/pwm/pwmchip0/export
	fi
	chgrp trab /sys/class/pwm/pwmchip0/device/pwm_period
	chmod g+w /sys/class/pwm/pwmchip0/device/pwm_period
	chgrp trab /sys/class/pwm/pwmchip0/pwm3/duty_cycle
	chmod g+w /sys/class/pwm/pwmchip0/pwm3/duty_cycle
	chgrp trab /sys/class/pwm/pwmchip0/pwm3/enable
	chmod g+w /sys/class/pwm/pwmchip0/pwm3/enable
    # gpio18 = 0 = out
	if [ ! -d /sys/class/gpio/gpio18 ] ; then
	    echo -n "18" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio18/direction
	echo -n "0" > /sys/class/gpio/gpio18/value
    # gpio19 = in = no pull-up nor pull-down
	if [ ! -d /sys/class/gpio/gpio19 ] ; then
	    echo -n "19" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio19/direction
    # gpio66 = 1
	if [ ! -d /sys/class/gpio/gpio66 ] ; then
	    echo -n "66" > /sys/class/gpio/export
	fi
	echo -n "1" > /sys/class/gpio/gpio66/value
	echo -n "1000000" > /sys/class/pwm/pwmchip0/device/pwm_period
	echo -n "500000" > /sys/class/pwm/pwmchip0/pwm3/duty_cycle
    echo -n "0" > /sys/class/pwm/pwmchip0/pwm3/enable

	### SERIAL INTERFACE SPI

    # IO10 = SPI #SS
	#	gpio26=0 (output)
	#	gpio27=1 (pull-up)
	#	gpio74=0 (IO10 is GPIO)
	if [ ! -d /sys/class/gpio/gpio26 ] ; then
	    echo -n "26" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio26/direction
	echo -n "0" > /sys/class/gpio/gpio26/value
	if [ ! -d /sys/class/gpio/gpio27 ] ; then
	    echo -n "27" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio27/direction
	echo -n "1" > /sys/class/gpio/gpio27/value
	if [ ! -d /sys/class/gpio/gpio74 ] ; then
	    echo -n "74" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio74/value
	if [ ! -d /sys/class/gpio/gpio10 ] ; then
	    echo -n "10" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio10/direction
	chgrp trab /sys/class/gpio/gpio10/value
    chmod g+rw /sys/class/gpio/gpio10/value

	# IO11 = SPI MOSI
	#	gpio24=0 (output)
	#	gpio25=input (floating)
	#	gpio44=1 (IO11 is SPI)
	#	gpio72=0 (IO11 is SPI)
	if [ ! -d /sys/class/gpio/gpio24 ] ; then
	    echo -n "24" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio24/direction
	echo -n "0" > /sys/class/gpio/gpio24/value
	
	if [ ! -d /sys/class/gpio/gpio25 ] ; then
	    echo -n "25" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio25/direction
	
	if [ ! -d /sys/class/gpio/gpio44 ] ; then
	    echo -n "44" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio44/direction
	echo -n "1" > /sys/class/gpio/gpio44/value
	
	if [ ! -d /sys/class/gpio/gpio72 ] ; then
	    echo -n "72" > /sys/class/gpio/export
	fi
	echo -n "0" > /sys/class/gpio/gpio72/value

	# IO12 = SPI MISO
	#	gpio42=1 (input)
	#	gpio43=input (floating)
	if [ ! -d /sys/class/gpio/gpio42 ] ; then
	    echo -n "42" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio42/direction
	echo -n "1" > /sys/class/gpio/gpio42/value
	if [ ! -d /sys/class/gpio/gpio43 ] ; then
	    echo -n "43" > /sys/class/gpio/export
	fi
	echo -n "in" > /sys/class/gpio/gpio43/direction

	# IO13 = SPI SCLK
	#	gpio30=0 (output)
	#	gpio31=0 (pull-down, SCLK mode 0)
	#	gpio46=1 (IO13 is SPI)
	if [ ! -d /sys/class/gpio/gpio30 ] ; then
	    echo -n "30" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio30/direction
	echo -n "0" > /sys/class/gpio/gpio30/value
	if [ ! -d /sys/class/gpio/gpio31 ] ; then
	    echo -n "31" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio31/direction
	echo -n "0" > /sys/class/gpio/gpio31/value
	if [ ! -d /sys/class/gpio/gpio46 ] ; then
	    echo -n "46" > /sys/class/gpio/export
	fi
	echo -n "out" > /sys/class/gpio/gpio46/direction
	echo -n "1" > /sys/class/gpio/gpio46/value
    chgrp trab /dev/spidev1.0
    chmod g+rw /dev/spidev1.0
   
	;;
    stop)
    # SENSORS
    echo -n "13" > /sys/class/gpio/unexport
	echo -n "34" > /sys/class/gpio/unexport
	echo -n "35" > /sys/class/gpio/unexport
	echo -n "77" > /sys/class/gpio/unexport
    echo -n "14" > /sys/class/gpio/unexport
	echo -n "16" > /sys/class/gpio/unexport
	echo -n "17" > /sys/class/gpio/unexport
	echo -n "76" > /sys/class/gpio/unexport
	echo -n "64" > /sys/class/gpio/unexport

    #H ENABLE
    echo -n "38" > /sys/class/gpio/unexport
	echo -n "39" > /sys/class/gpio/unexport

    #PWM 
    echo -n "0" > /sys/class/pwm/pwmchip0/pwm3/enable
    echo -n "66" > /sys/class/gpio/unexport
	echo -n "19" > /sys/class/gpio/unexport
	echo -n "1" > /sys/class/gpio/gpio18/value
	echo -n "18" > /sys/class/gpio/unexport
	echo -n "1" > /sys/class/pwm/pwmchip0/unexport

    #SPI
    echo -n "1" > /sys/class/gpio/gpio26/value
	echo -n "26" > /sys/class/gpio/unexport
	echo -n "in" > /sys/class/gpio/gpio27/direction
	echo -n "74" > /sys/class/gpio/unexport
	echo -n "1" > /sys/class/gpio/gpio24/value
	echo -n "24" > /sys/class/gpio/unexport
	echo -n "25" > /sys/class/gpio/unexport
	echo -n "0" > /sys/class/gpio/gpio44/value
	echo -n "44" > /sys/class/gpio/unexport
	echo -n "72" > /sys/class/gpio/unexport
	echo -n "10" > /sys/class/gpio/unexport
	echo -n "42" > /sys/class/gpio/unexport
	echo -n "43" > /sys/class/gpio/unexport
	echo -n "0" > /sys/class/gpio/gpio46/value
	echo -n "46" > /sys/class/gpio/unexport
	echo -n "in" > /sys/class/gpio/gpio31/direction
	echo -n "31" > /sys/class/gpio/unexport	
	echo -n "1" > /sys/class/gpio/gpio30/value
	echo -n "30" > /sys/class/gpio/unexport

   	;;
    status)
        #SENSORS
    	ls -d /sys/class/gpio/gpio*

        #PWM 
        echo -n Period:
    	cat /sys/class/pwm/pwmchip0/device/pwm_period
    	echo -n Duty Cicle:
    	cat /sys/class/pwm/pwmchip0/pwm1/duty_cycle
    	echo -n Enable:
    	cat /sys/class/pwm/pwmchip0/pwm1/enable
	;;
    *)
	echo -n "Usage: $0 " 
	echo "{start|stop|restart|force-reload|status}"
	exit 1
	;;
esac

exit 0
