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
	while notReceivedYet>0:
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


def receiver2(receiverSocket, router2address):
	# use global variables
	global receivedInput, notReceivedYet, startTime

	# create a socket and assign given port to it.
	senderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	# in order not to get the address already in use error
	senderSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# bind the socket to port
	senderSocket.bind(('', router2address[1]))

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
				print("Ack is sending to router 2 for packet sequence number: ", incomingSeqNumber)
				senderSocket.sendto(ackPacket, router2address)
				if incomingSeqNumber == 0:
					for i in range(10):
						senderSocket.sendto(ackPacket, router2address)
	takenTime = time.time() - startTime
	print("time taken by sending process is :", takenTime)
	# close the connection when all the data is transmitted
	receiverSocket.close()


if __name__ == "__main__":

	'''Receiver Socket from Router 1'''
	# router1 listen address in destination
	r1ListenAddr = ('10.10.4.2', 20448)

	# create an IPv4 socket by using UDP
	r1Socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	r1Socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	r1Socket.bind(r1ListenAddr)

	'''Receiver Socket from Router 2'''
	# router2 listen address in destination
	r2ListenAddr = ('10.10.5.2', 20443)

	# create an IPv4 socket by using UDP
	r2Socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	r2Socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	r2Socket.bind(r2ListenAddr)

	'''Sending address to router 1'''
	r1SendAddr = ('10.10.4.1', 20447)

	'''Sending address to router 2'''
	r2SendAddr = ('10.10.5.1', 20442)

	for i in range(5556):
		receivedInput.append("")

	receiveLock = Lock()

	receiverThread1 = Thread(target=receiver, args=(r1Socket, r1SendAddr, ))
	receiverThread1.start()

	receiverThread2 = Thread(target=receiver2, args=(r2Socket, r2SendAddr, ))
	receiverThread2.start()

	receiverThread1.join()
	receiverThread2.join()

	outputFile = open("output2.txt", 'w+')
	for data in receivedInput:
		outputFile.write(data)
	outputFile.close()
