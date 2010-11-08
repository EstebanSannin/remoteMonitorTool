#!/bin/sh

echo Content-type: text/html
echo ""

echo "NETSTAT TCP/UDP CONNECTION:"
echo ""
netstat -n -ut | grep ESTA


