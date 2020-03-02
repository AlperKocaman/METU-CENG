from socket import * # for python Socket API
import time # for timestamp data
from threading import Thread # for handling multiple requests

# a method for creating UDP client threads in order to send data to servers
def client(ipv4, port, targetNode):
    # an IPv4 socket is created with UDP
    # AF_INET is Internet protocol v4 adress family.
    # SOCK_DGRAM is a datagram-based protocol
    _client = socket(AF_INET, SOCK_DGRAM)
    _client.bind(('',port))# binding adress

    totalDelay = 0.0 # to keep total delay time 
    delay = 0.0 # to keep delay for 1 message   

    i = 0
    while i < 1000:
        # in order to send request to specified destination
        _client.sendto(str(time.time()).encode(),(ipv4,port))
        # try to receive data  
        reply, address = _client.recvfrom(1024)
        if reply.decode() == "ACK": # R3 node received our message
            i+=1
    _client.close()
        
# a method for creating UDP server threads in order to receive data from clients
def server(port):
    # create a socket and assign given port to it.
    _server = socket(AF_INET, SOCK_DGRAM)
    _server.bind(('',port))
    try:
        i = 0
        while i < 1000:
            data, address = _server.recvfrom(1000) # receive data from the client
            if data:
                i+=1
                _server.sendto(data,address) # if data is not empty send it back
    finally:
        _server.close()
    
# create client to send data
clientR3 = Thread(target=client, args=('10.10.3.2',20450,"R3")) # R3
clientR3.start()