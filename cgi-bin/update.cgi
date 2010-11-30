#!/bin/sh

echo Content-type: text/html
echo ""

echo "Update package"
apt-get update >> update.log &
tail -n12 update.log 



