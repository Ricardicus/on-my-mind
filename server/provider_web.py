#!/usr/bin/env python3
import zmq
import datetime
import socket as sp

HOST = 'localhost' # Change to WAN before using. 
PORT = 7680     

PROVIDER_SOCKET = "ipc:///tmp/provider_ipc"

if __name__=="__main__":
    context = zmq.Context()
    socket = context.socket(zmq.SUB)
    socket.setsockopt_string(zmq.SUBSCRIBE, "")
    socket.connect (PROVIDER_SOCKET)

    print("Make sure your IP is reachable.")
    print("If your behind a NAT router (such as a WiFi),")
    print("you must do port forwarding before anyone can reach you.")
    HOST = input("Enter you WAN adress, make sure its reachable:\n")
    try:
        PORT = int(input("Enter the port your hosting the service on."))
    except ValueError:
        print("Please a valid port number.")
        exit(1)

    with sp.socket(sp.AF_INET, sp.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        while True:
            conn, addr = s.accept()
            with conn:
                print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + ":", 'Connected by', addr)
                string = socket.recv()
                print("Sending: " + str(string))
                while True:
                    data = conn.recv(1024)
                    conn.sendall(string)
                    conn.close()
                    break
