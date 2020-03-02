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
# our window size is 20, that means we send 20 packets and wait until packet acknowledgments come
windowSize = 20
# if no response is taken in 5 second, this packet is assumed to be lost
TimeOut = 0.5
# base number of the window size, it will increase by 1 for each correct Ack
base1 = 0
# next packet number that is ready to be sent
nextPacket1 = 0


def readInputFile(fileName):

	sequenceNumber = 0                  # sequenceNumber
	inputFile = open(fileName, "rb")    # open the input file in binary format since given input file in binary format.
	packet = inputFile.read(900)        # read the first 900 bytes

	# parse the file till the end of file
	while packet:

		# packet should contain sequence number
		packet = struct.pack("i", sequenceNumber) + packet

		if sequenceNumber == 0:
			packet = packet + struct.pack("d", time.time())
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


def sender(router3Address):
	# in order to use below variables from global variables
	global base1, windowSize, nextPacket1, timer1

	# create a socket and assign given port to it.
	senderSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	# in order not to get the address already in use error
	senderSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	# bind the socket to port
	senderSocket.bind(('', router3Address[1]))

	maxSize = base1 + windowSize
	try:
		# continue sending while there are packets left not sent.
		while base1 <= 5555:
			# send packets according to window size
			while nextPacket1 < maxSize:
				print("Sending packet with sequence number :", nextPacket1)
				# send next packet via senderSocket
				senderSocket.sendto(combinedDataList[nextPacket1], router3Address)
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


def resendLostMessage(senderNum):
	# handles the lost packages like go-back N strategy
	# in order to retransmit all the packets from base, we need to change nextPacket
	# use global vars
	global nextPacket1, base1, resendLock
	# use lock in order to reach shared resource
	with resendLock:
		if senderNum == 0:
			nextPacket1 = base1


'''The functionality of below method is, it takes the incoming "ACK" messages from routers '''


def receiver(receiverSocket):
	# in order to use below variables from global variables
	global base1, timer1, receiveLock

	try:
		# while there are unsent packets
		while base1 <= 5555:
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
							timer1.cancel()
							base1 += 1
			else:
				# wait for timer to timeout
				print("Couldn't sent packet correctly with id: ", )
	finally:
		receiverSocket.close()

if __name__ == "__main__":
	# read the input file and stores them in chunks
	readInputFile("input.txt")

	''' Receiver socket from Router 3'''
	# router1 listen address in source
	r3ListenAddr = ('10.10.3.1', 20451)

	# create an IPv4 socket by using UDP
	router3Socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	# In order not to get the address already in use error
	router3Socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

	#  Binds listening port to created socket
	router3Socket.bind(r3ListenAddr)

	'''Sending address to Router3'''
	r3SendAddr = ('10.10.3.2', 20450)

	nextPacket1 = 0
	base1 = 0

	for i in range(len(combinedDataList)):
		dataReceivedByDestination.append(False)

	baseLock = Lock()
	receiveLock = Lock()
	windowLock = Lock()
	resendLock = Lock()

	receiverThread1 = Thread(target=receiver, args=(router3Socket, ))
	receiverThread1.start()

	timer1 = Timer(TimeOut, resendLostMessage, args=(0,))
	senderThread1 = Thread(target =sender, args = (r3SendAddr, ))
	senderThread1.start()

	receiverThread1.join()
	senderThread1.join()
