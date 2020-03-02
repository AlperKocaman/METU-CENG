# used for generating md5 Checksums
import hashlib
# for python Socket API
import socket
# used in encoding messages
import struct
# used to generate timestamps
import time
# used for multithreaded structure
from threading import *

# use CombinedPacketList for containing all packets to be ready to sent <index,md5,data>
combinedPacketList = []



'''The functionality of below method is, it takes the incoming packet 
 from source and save to the combinedPacketList list'''


def receiverFromSource(receiverSocket, destAddress):

	# create a socket and assign given port to it.
	senderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	# in order not to get the address already in use error
	senderSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# bind the socket to port
	senderSocket.bind(('', destAddress[1]))

	# in order to receive all packets come from source, this thread needs to work all the time
	while True :
		# take the incoming data from source, it will be at most 1000 bytes
		data, address = receiverSocket.recvfrom(1000)
		# if the incoming packet is not null, process it
		if data:
			# extract the incoming md5 Checksum, it is 32 hexadecimal digits
			incomingChecksum = struct.unpack("32s", data[:32])[0]
			# calculate the checksum for incoming packet, except for the first md5Checksum data
			calculatedChecksum = hashlib.md5(data[32:]).hexdigest()
			# if calculated and incoming checksums are equal, the incoming packet is not corrupted
			if calculatedChecksum == incomingChecksum:
				# extract the incoming sequence number in order to place it to correct place in combinedPacketList
				incomingSeqNumber = struct.unpack("i", data[32:36])[0]
				combinedPacketList[incomingSeqNumber] = data
				print("Sending packet with sequence number :", incomingSeqNumber)
				senderSocket.sendto(data, destAddress)
				# since global variable ready data is shared between threads, it needs to be synchronized

	# although below code is unreachable, I wrote it since it is needed in socket programming.
	_receiver.close()


'''The functionality of below method is, it takes the incoming "ACK" messages
	from destination and send them to the source '''


def ackReceiverSender(ackReceiverSocket, sourceAddr):

	# create a socket for sending "Ack" messages to source by using UDP
	ackSenderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	# in order not to get the address already in use error
	ackSenderSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# bind the socket to port
	ackSenderSocket.bind(('', sourceAddr[1]))
	# need to loop forever since incoming or outgoing "ACK" messages can be lost
	# especially we do this solution since there is no need to shutdown routers
	while True:
		# take the incoming packet, it will be at most 1000 bytes although it is a lot smaller
		data, address = ackReceiverSocket.recvfrom(1000)
		# if the incoming packet is not null, process it
		if data:
			# extract the incoming md5 Checksum, it is 32 hexadecimal digits
			incomingChecksum = struct.unpack("32s", data[:32])[0]
			# calculate the checksum for incoming packet
			calculatedChecksum = hashlib.md5(data[32:]).hexdigest()
			# if calculated and incoming checksums are equal, the incoming packet is not corrupted.
			if incomingChecksum == calculatedChecksum:
				# send back ackPacket to source
				ackSenderSocket.sendto(data, sourceAddr)

	# although below codes are unreachable, I wrote them since they are needed in socket programming.
	ackSenderSocket.close()
	ackReceiverSocket.close()


if __name__ == "__main__":

	'''Receiver Socket from Source'''
	# source listen address in router2
	sourceListenAddr = ('10.10.2.1', 20440)

	# create an IPv4 socket by using UDP
	sourceSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	sourceSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	sourceSocket.bind(sourceListenAddr)

	'''Receiver Socket from Destination'''
	# destination listen address in router2
	destListenAddr = ('10.10.5.1', 20442)

	# create an IPv4 socket by using UDP
	socketDest = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	socketDest.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	socketDest.bind(destListenAddr)

	'''Sending address to Source'''
	sourceSendAddr = ('10.10.2.2', 20441)

	'''Sending address to Destination'''
	destSendAddr = ('10.10.5.2', 20443)

	for i in range(5556):
		combinedPacketList.append("")

	dataListLock = Lock()

	receiverThread1 = Thread(target=receiverFromSource, args=(sourceSocket, destSendAddr, ))
	receiverThread1.start()

	ackReceiverSenderThread = Thread(target=ackReceiverSender, args=(socketDest, sourceSendAddr,))
	ackReceiverSenderThread.start()


	'''Below join methods will not be happened so this script will not be terminated automatically '''
	receiverThread1.join()
	ackReceiverSenderThread.join()
