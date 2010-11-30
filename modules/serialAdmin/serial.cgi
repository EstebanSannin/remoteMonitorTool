#!/bin/sh

echo Content-type: text/html
echo ""

LOG_SERIAL=serial.log
#stty -F /dev/tty
echo "serial.log:"
echo
if [ -e $LOG_SERIAL ]; then
	tail $LOG_SERIAL
else	
	echo "[LOG]: Generating serial.log"
	cat /dev/ttyS0 >> $LOG_SERIAL &
	tail $LOG_SERIAL

fi


