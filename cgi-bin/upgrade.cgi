#!/bin/sh

echo Content-type: text/html
echo ""

echo "Update package"
apt-get -f upgrade >> upgrade.log &
tail -n12 upgrade.log 



