#!/bin/bash

SERVER="192.168.68.104"
PORT="7680"

which nc >/dev/null
if [ ! $? -eq 0 ]; then
	printf "\e[1mOh no!\e[0m You don't have the program 'nc' needed for this to work.. \e[5mContact Rickard!\e[0m\n"
	exit 1
fi

msg=$(echo hej | nc $SERVER $PORT )
echo $msg