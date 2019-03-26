#!/bin/bash

SERVER="192.168.68.104"
PORT="7680"

which nc >/dev/null
if [ ! $? -eq 0 ]; then
	echo -e "\e[m4Oh no!\e[m0 You don't have the program 'nc' needed for this to work.. Contact Rickard!"
fi

msg=$(echo hej | nc $SERVER $PORT )
echo $msg