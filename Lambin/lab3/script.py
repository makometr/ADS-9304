#!/usr/bin/python3
import os

os.system('touch result.txt')
print('______________________________')
for i in range(1, 6):
	inputFileDirection = './tests/test{}.txt'.format(i)
	outputFileDirection = './tests/output{}.txt'.format(i)
	os.system('./lab3 {} result.txt'.format(inputFileDirection))

	inputFile = open(inputFileDirection, 'r')
	outputFile = open(outputFileDirection, 'r')
	result = open('result.txt', 'r')
	out = outputFile.read()
	print('INPUT:\n\t{}'.format(inputFile.read()))
	print('OUTPUT:\n\t{}'.format(out))
	if out == result.read():
		print('CORRECT')
	else:
		print('INCORRECT')
	print('______________________________')
	inputFile.close()
	outputFile.close()
	result.close()

for i in range(1, 3):
	inputFileDirection = './tests/errors{}.txt'.format(i)
	os.system('./lab3 {} 2> result.txt'.format(inputFileDirection))

	inputFile = open(inputFileDirection, 'r')
	result = open('result.txt', 'r')
	res = result.read()
	print('INPUT:\n\t{}'.format(inputFile.read()))
	print('OUTPUT:\n\t{}'.format(res))
	if res == 'Error: expression is incorrect\n':
		print('CORRECT')
	else:
		print('INCORRECT')
	print('______________________________')
	inputFile.close()
	result.close()

os.system('rm -rf result.txt')
