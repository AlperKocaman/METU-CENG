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

# create an array to keep correctly received inputs
receivedInput = []
# not received packet number
notReceivedYet = 5556
startTime = 0

def receiver(receiverSocket, router1address):
	# use global variables
	global receivedInput, notReceivedYet, startTime

	# create a socket and assign given port to it.
	senderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	# in order not to get the address already in use error
	senderSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# bind the socket to port
	senderSocket.bind(('', router1address[1]))

	# iterate when there are packets left unreceived
	while notReceivedYet > 0:
		# take the incoming packet
		data, address = receiverSocket.recvfrom(1000)
		# if incoming data is not null, process it
		if data:
			# extract the incoming packet's md5Checksum
			incomingChecksum = struct.unpack("32s", data[:32])[0]
			data = data[32:]
			# calculate the incoming packet's md5 Checksum
			calculatedChecksum = hashlib.md5(data).hexdigest()
			if calculatedChecksum == incomingChecksum:
				# extract the incoming sequence number
				incomingSeqNumber = struct.unpack("i", data[:4])[0]
				data = data[4:]
				# place the data to correct place in received input
				if incomingSeqNumber == 0:
					startTime = struct.unpack("d", data[-8:])[0]
					data = data[:-8]
				if receivedInput[incomingSeqNumber] == "":
					notReceivedYet -= 1
					receivedInput[incomingSeqNumber] = data
				# pack sequence number and data
				ackPacket = struct.pack("i", incomingSeqNumber) + struct.pack("3s", "ACK")
				# calculate checksum
				ackPacketChecksum = hashlib.md5(ackPacket).hexdigest()
				# place ackPacketChecksum to packet
				ackPacket = struct.pack("32s", ackPacketChecksum) + ackPacket
				# send back ackPacket to relevant router
				print("Ack is sending to router 1 for packet sequence number: ", incomingSeqNumber)
				senderSocket.sendto(ackPacket, router1address)
				if incomingSeqNumber == 5555:
					for i in range(10):
						senderSocket.sendto(ackPacket, router1address)

	takenTime = time.time() - startTime
	print("time taken by sending process is :", takenTime)
	# close the connection when all the data is transmitted
	receiverSocket.close()

if __name__ == "__main__":

	'''Receiver Socket from Router 1'''
	# router1 listen address in destination
	r3ListenAddr = ('10.10.7.1', 20453)

	# create an IPv4 socket by using UDP
	r3Socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	r3Socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	r3Socket.bind(r3ListenAddr)

	'''Sending address to router 3'''
	r3SendAddr = ('10.10.7.2', 20452)

	for i in range(5556):
		receivedInput.append("")

	receiverThread1 = Thread(target=receiver, args=(r3Socket, r3SendAddr, ))
	receiverThread1.start()

	receiverThread1.join()

	outputFile = open("output.txt", 'w+')
	for data in receivedInput:
		outputFile.write(data)
	outputFile.close()
