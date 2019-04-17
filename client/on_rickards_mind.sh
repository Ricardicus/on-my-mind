#!/bin/bash

SERVER="90.230.94.128"
PORT="7658"

VERSION_FILE=".moddate"

which nc >/dev/null
if [ ! $? -eq 0 ]; then
	printf "\e[1mOh no!\e[0m You don't have the program 'nc' needed for this to work.. \e[5mContact Rickard!\e[0m\n"
	exit 1
fi

msg=$(echo hej | nc $SERVER $PORT )
moddate=$(echo "$msg" | sed 's/\(.*\)\@\(.*\)/\1/')
display=$(echo "$msg" | sed 's/\(.*\)\@\(.*\)/\2/')

if [ ! -f "$VERSION_FILE" ]; then
	echo "Initial" > $VERSION_FILE
fi

oldmoddate=$(cat $VERSION_FILE)

if [ "$moddate" != "$oldmoddate" ]; then
	printf "\e[1mRickard has updated the content! Last modified: $moddate\e[0m\n"
fi

echo $display

printf "$moddate" > $VERSION_FILE
