import unittest
import subprocess
import os	


class TestLab1(unittest.TestCase):

	def SuccessTest(self):
		with open('Tests/SuccessTests.txt', 'r') as file:
			print('Success tests:\n')
			for line in file:
				ster = line.replace('\n', '')
				os.system("./lab1 " + ster)

			print('\n--------------------------------\n')

	def ErrorTest(self):
		with open('Tests/ErrorTests.txt', 'r') as file:
			print('Error tests:\n')
			for line in file:
				ster = line.replace('\n', '')
				os.system("./lab1 " + ster)
			print('\n--------------------------------\n')


tt = TestLab1()
tt.SuccessTest()
tt.ErrorTest()
