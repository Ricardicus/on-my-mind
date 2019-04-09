#!/bin/bash

SERVER="90.230.94.128"
PORT="7658"

which nc >/dev/null
if [ ! $? -eq 0 ]; then
	printf "\e[1mOh no!\e[0m You don't have the program 'nc' needed for this to work.. \e[5mContact Rickard!\e[0m\n"
	exit 1
fi

msg=$(echo hej | nc $SERVER $PORT )
echo $msg
