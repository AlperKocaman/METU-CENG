from socket import * # for python Socket API
import time # for timestamp data
from threading import Thread # for handling multiple requests

# a method for creating UDP client threads in order to send data to servers
def client(ipv4, port, targetNode):
    # an IPv4 socket is created with UDP
    # AF_INET is Internet protocol v4 adress family.
    # SOCK_DGRAM is a datagram-based protocol
    _client = socket(AF_INET, SOCK_DGRAM)
    _client.bind(('',port))

    totalDelay = 0.0 # to keep total delay time 
    delay = 0.0 # to keep delay for 1 message   

    i = 0
    while i < 1000:
        # in order to send request to specified destination
        _client.sendto(str(time.time()).encode(),(ipv4,port))
        # try to receive data  
        reply, address = _client.recvfrom(1024)
        if reply:
            #if reply is not empty calculate the delay and add it to totalDelay, then print it 
            i+=1
            delay = time.time()-float(reply);
            totalDelay += delay
            print(_client.getsockname(), delay)

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
                print(time.time() - float(data.decode())) # print the delay fro the source node to destination node
    finally:
        _server.close()

# create a server to receive data
serverR3 = Thread(target=server, args=(20452,)) # R3
serverR3.start()