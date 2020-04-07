def modPower(exp, n, b):
	result = 1
	for bit in exp:
		result = (result * result) % n
		if bit == 1:
			result = (b * result) % n
	return result

def main():
	cipherText = input()
	n = input()

	cipherText = int(cipherText, 16)
	n = int(n, 16)
	powerFile = open("ptrace.trc", "r")

	exponentList = []
	successives = 0
	control = False

	for line in powerFile:
		if float(line) >= 7.5:
			control = True
			successives += 1
		elif control:
			if successives == 75:
				exponentList += [0]  #just square case
			elif successives == 125:
				exponentList += [1]  #both square and multiplication case
			successives = 0
			control = False

	message = modPower(exponentList, n, cipherText)
	message = format(message, 'x')
	print(bytearray.fromhex(message).decode(),end="")


if __name__ == "__main__":

	main()