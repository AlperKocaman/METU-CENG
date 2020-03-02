from socket import * # for python Socket API
import time # for timestamp data
from threading import Thread # for handling multiple requests

# a method for creating UDP client threads in order to send data to servers AND 
#   UDP server thread in order to receive data from clients
def server(port):
    _server = socket(AF_INET, SOCK_DGRAM)# for listening to source node
    _server.bind(('',port))
    _client = socket(AF_INET, SOCK_DGRAM)# for sending data to destination node
    _client.bind(('',20452))
    try:
        i = 0
        while i < 1000:
            data, address = _server.recvfrom(1000) # receive data from source
            if data:
                i+=1
                _client.sendto(data,('10.10.7.1',20452)) # send data to destination
                _server.sendto(b'ACK',('10.10.3.1',port)) # send acknowledgement message to source
    finally:
        _server.close()
        _client.close()
    

# create a server and client to receive and send data
serverSource = Thread(target = server, args = (20450,)) # Source - destination
serverSource.start()