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

# use CombinedDataList for containing all packets to be ready to sent <md5, index, data>
combinedDataList = []
# create a bool array to check whether or not the packet at index is sent or not for all the packets
dataReceivedByDestination = []
# our actual window size is 20, that means we send 20 packets and wait until packet acknowledgments come
# however, since we are doing double sided transmission, it is set as 10
windowSize = 10
# if no response is taken in 0.5 second, this packet is assumed to be lost
TimeOut = 0.5
# base numbers of the window size, they will be increased or decreased by 1 for each correct Ack
base1 = 0
base2 = 5555
# next packet numbers that are ready to be sent
nextPacket1 = 0
nextPacket2 = 5555

'''Below function functionality is, it reads the 5mb input file and
 stores them in at most 1000 bytes(actually 936 bytes) packets '''


def readInputFile(fileName):

	sequenceNumber = 0                  # sequenceNumber
	inputFile = open(fileName, "rb")    # open the input file in binary format since given input file in binary format.
	packet = inputFile.read(900)        # read the first 900 bytes

	# parse the file till the end of file
	while packet:

		# packet should contain sequence number
		packet = struct.pack("i", sequenceNumber) + packet

		# take the checksum of the constructed file
		# use hashlib.md5() function as a md5Checksum function
		checksum = hashlib.md5(packet).hexdigest()

		# packet should also contain md5 checksum of the file
		# append the packet in the combinedData list
		packet = struct.pack("32s", checksum.encode()) + packet
		combinedDataList.append(packet)
		# read the new 900 bytes from "input.txt"
		packet = inputFile.read(900)
		sequenceNumber += 1

	# at this point, program has ready to sent file as a chunks(exactly there are 5556 chunks)


def sender(router1Address):
	# in order to use below variables from global variables
	global base1, base2, windowSize, nextPacket1, timer1

	# create a socket and assign given port to it.
	senderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	# in order not to get the address already in use error
	senderSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# bind the socket to port
	senderSocket.bind(('', router1Address[1]))

	maxSize = base1 + windowSize
	try:
		# continue sending while there are packets left not sent.
		while base1 <= base2:
			# send packets according to window size
			while nextPacket1 < maxSize:
				print("Sending packet with sequence number :", nextPacket1)
				# send next packet via senderSocket
				senderSocket.sendto(combinedDataList[nextPacket1], router1Address)
				# since base 1 is shared, it needs synchronization mechanism
				with baseLock:
					# if it is the first packet in the window, set the timer
					if base1 == nextPacket1:
						timer1.cancel()
						timer1 = Timer(TimeOut, resendLostMessage, args=(0, ))
						timer1.start()
					nextPacket1 += 1
			# shift the window according to total packet count
			if base1 + windowSize < len(combinedDataList):
				maxSize = base1 + windowSize
			else:
				maxSize = len(combinedDataList)

	finally:
		senderSocket.close()


def sender2(router2Address):
	# in order to use below variables from global variables
	global base1, base2, windowSize, nextPacket2, timer2

	# create a socket and assign given port to it.
	senderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	# in order not to get the address already in use error
	senderSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# bind the socket to port
	senderSocket.bind(('', router2Address[1]))

	maxSize = base2 - windowSize
	try:
		# continue sending while there are packets left not sent.
		while base1 <= base2:
			# send packets according to window size
			while nextPacket2 > maxSize:
				print("Sending packet with sequence number :", nextPacket2)
				# send next packet via senderSocket
				senderSocket.sendto(combinedDataList[nextPacket2], router2Address)
				# since base 2 is shared, it needs synchronization mechanism
				with baseLock:
					# if it is the first packet in the window, set the timer
					if base2 == nextPacket2:
						timer2.cancel()
						timer2 = Timer(TimeOut, resendLostMessage, args=(1, ))
						timer2.start()
					nextPacket2 -= 1

			# shift the window according to total packet count
			if base2 - windowSize > -1:
				maxSize = base2 - windowSize
			else:
				maxSize = -1

	finally:
		senderSocket.close()


'''The below function responsibility is that it changes base values so that other threads send lost packets again'''


def resendLostMessage(senderNum):
	# handles the lost packages like go-back N strategy
	# in order to retransmit all the packets from base, we need to change nextPacket
	# use global vars
	global nextPacket1, nextPacket2, base1, base2, resendLock
	# use lock in order to reach shared resource
	with resendLock:
		if senderNum == 0:
			nextPacket1 = base1
		else:
			nextPacket2 = base2


'''The functionality of below method is, it takes the incoming "ACK" messages from routers '''


def receiver(receiverSocket):
	# in order to use below variables from global variables
	global base1, base2, timer1, timer2, receiveLock

	try:
		# while there are unsent packets
		while base1 <= base2:
			# receive data from the routers
			data, address = receiverSocket.recvfrom(1000)
			# if data is not null, process it
			if data:
				print("Data came")
				# extract the checksum that is embedded in incoming packet
				incomingChecksum = struct.unpack("32s", data[:32])[0]
				# throw the first 32 bytes of data
				data = data[32:]
				# calculate the checksum of the incoming packet
				calculatedChecksum = hashlib.md5(data).hexdigest()
				# if checksums are equal
				if incomingChecksum == calculatedChecksum:
					sequenceNum = struct.unpack("i", data[0:4])[0]
					dataReceivedByDestination[sequenceNum] = True
					with baseLock:
						if sequenceNum == base1:
							base1 += 1
						elif sequenceNum == base2:
							base2 -= 1
			else:
				# wait for timer to timeout
				print("Couldn't sent packet correctly with id: ", )
	finally:
		receiverSocket.close()


def receiver2(receiverSocket):
	# in order to use below variables from global variables
	global base1, base2, timer1, timer2, receiveLock

	try:
		# while there are unsent packets
		while base1 <= base2:

			# receive data from the routers
			data, address = receiverSocket.recvfrom(1000)
			# if data is not null, process it
			if data:
				print("Data came")
				# extract the checksum that is embedded in incoming packet
				incomingChecksum = struct.unpack("32s", data[:32])[0]
				# throw the first 32 bytes of data
				data = data[32:]
				# calculate the checksum of the incoming packet
				calculatedChecksum = hashlib.md5(data).hexdigest()
				# if checksums are equal
				if incomingChecksum == calculatedChecksum:
					sequenceNum = struct.unpack("i", data[0:4])[0]
					dataReceivedByDestination[sequenceNum] = True
					with baseLock:
						if sequenceNum == base1:
							base1 += 1
						elif sequenceNum == base2:
							base2 -= 1
			else:
				# wait for timer to timeout
				print("Couldn't sent packet correctly with id: ", )
	finally:
		receiverSocket.close()

if __name__ == "__main__":
	# read the input file and stores them in chunks
	readInputFile("input.txt")

	''' Receiver socket from Router 1'''
	# router1 listen address in source
	r1ListenAddr = ('10.10.1.1', 20446)

	# create an IPv4 socket by using UDP
	router1Socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	router1Socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	router1Socket.bind(r1ListenAddr)

	'''Receiver Socket from Router 2'''
	# router2 listen address in source
	r2ListenAddr = ('10.10.2.2', 20441)

	# create an IPv4 socket by using UDP
	router2Socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	router2Socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	router2Socket.bind(r2ListenAddr)

	'''Sending address to Router 1'''
	r1SendAddr = ('10.10.1.2', 20445)

	'''Sending address to Router 2'''
	r2SendAddr = ('10.10.2.1', 20440)

	# in order to set all elements of dataReceivedByDestination bool array as false initially
	for i in range(len(combinedDataList)):
		dataReceivedByDestination.append(False)

	baseLock = Lock()
	receiveLock = Lock()
	resendLock = Lock()

	receiverThread1 = Thread(target=receiver, args=(router1Socket, ))
	receiverThread1.start()

	receiverThread2 = Thread(target=receiver2, args=(router2Socket, ))
	receiverThread2.start()

	timer1 = Timer(TimeOut, resendLostMessage, args=(0, ))
	senderThread1 = Thread(target =sender, args = (r1SendAddr, ))
	senderThread1.start()

	timer2 = Timer(TimeOut, resendLostMessage, args=(1,))
	senderThread2 = Thread(target =sender2, args = (r2SendAddr, ))
	senderThread2.start()

	receiverThread1.join()
	receiverThread2.join()
	senderThread1.join()
	senderThread2.join()
