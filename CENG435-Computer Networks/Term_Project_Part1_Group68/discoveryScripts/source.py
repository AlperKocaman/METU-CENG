from socket import * # for python Socket API
import time # for timestamp data
from threading import Thread # for handling multiple requests

# a method for creating UDP client threads in order to request data from servers
def client(ipv4, port, targetNode):
    # an IPv4 socket is created with UDP
    # this socket provides communication between R3&Source nodes, R3&R2 nodes and R3&Destination nodes
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
        if reply:
            #if reply is not empty calculate the delay and add it to totalDelay, then print it 
            i+=1
            delay = time.time()-float(reply);
            totalDelay += delay
            print(_client.getsockname(), delay)

    f = open(targetNode + "-R3_link_cost.txt", "w")           # opens a file 
    f.write(str(totalDelay/1000.0))                           # writes avg. delay to opened file    
    f.close()                                                 # closes the file
    _client.close()  
        
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
        
# create servers to receive data on different threads
serverR1 = Thread(target=server, args=(20445,)) # R1
serverR1.start()

serverR2 = Thread(target=server, args=(20448,)) # R2
serverR2.start()

serverR3 = Thread(target=server, args=(20450,)) # R3
serverR3.start()