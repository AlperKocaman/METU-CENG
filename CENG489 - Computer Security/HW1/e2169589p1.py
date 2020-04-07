def extendedGCD(e1, e2):

	e1s = 1
	e1t = 0
	e2s = 0
	e2t = 1

	turnFlag = True

	while (e1 != 0) and (e2 != 0):
		if turnFlag:
			quotient = (e1//e2)
			e1 -= quotient*e2
		else:
			quotient = (e2 // e1)
			e2 -= quotient * e1
		tempe1s = e1s
		e1s = e1t
		e1t = tempe1s - quotient * e1t
		tempe2s = e2s
		e2s = e2t
		e2t = tempe2s - quotient * e2t
		turnFlag = not(turnFlag)

	return e1s, e2s

def main():

	csvFile = open("crackme.csv", "r")
	for i in range(5):
		type = csvFile.read(1)
		if type == "c":
			if csvFile.read(1) == "1":
				csvFile.read(1)
				value = csvFile.readline()
				cipherText1 = int(value, 16)
			else:
				csvFile.read(1)
				value = csvFile.readline()
				cipherText2 = int(value, 16)
		elif type == "e":
			if csvFile.read(1) == "1":
				csvFile.read(1)
				value = csvFile.readline()
				e1 = int(value, 16)
			else:
				csvFile.read(1)
				value = csvFile.readline()
				e2 = int(value, 16)
		elif type == "n":
			csvFile.read(1)
			value = csvFile.readline()
			n = int(value, 16)

	x,y = extendedGCD(e1, e2)

	if x<0:
		cipherText1, x2 = extendedGCD(cipherText1, n)
		x *= -1

	if y<0:
		cipherText2, y2 = extendedGCD(cipherText2, n)
		y *= -1

	c1 = pow(cipherText1, x, n)
	c2 = pow(cipherText2, y, n)
	message = (c1 * c2) % n

	message = format(message, 'x')
	print(bytearray.fromhex(message).decode(), end="")


if __name__ == "__main__":

	main()

