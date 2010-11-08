#!/bin/sh

echo Content-type: text/html
echo ""

LOG_DMESG=dmesg.log
#echo "<pre>"
#cat log
#echo "LOG SYSTEM"

dmesg | tail -n12
#dmesg

#echo "</pre>"
