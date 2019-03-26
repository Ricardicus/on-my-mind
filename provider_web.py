#!/usr/bin/env python3
import zmq
import datetime
import socket as sp

HOST = '192.168.68.104'  # Standard loopback interface address (localhost)
PORT = 7680        # Port to listen on (non-privileged ports are > 1023)

PROVIDER_SOCKET = "ipc:///tmp/provider_ipc"

if __name__=="__main__":
    context = zmq.Context()
    socket = context.socket(zmq.SUB)
    socket.setsockopt_string(zmq.SUBSCRIBE, "")
    socket.connect (PROVIDER_SOCKET)

    with sp.socket(sp.AF_INET, sp.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        while True:
            conn, addr = s.accept()
            with conn:
                print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + ":", 'Connected by', addr)
                string = socket.recv()

                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    conn.sendall(string)
