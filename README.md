# Program used to let me pick your brain

This program consists of a backend, intended to run on a raspberry PI with 
ZMQ installed, and a frontend having netcat installed. 

# Prerequisites

The backend needs [ZMØ](http://zeromq.org/) and a C compiler. 
It also needs to be a UNIX machine. I use ipc sockets, named pipes,
which are not implemented in Windows. 
The frontend is a simple bash script that just needs [netcat](http://netcat.sourceforge.net/).
