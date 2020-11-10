import unittest
import subprocess
import os
import sys


class TestLab(unittest.TestCase):

	def SuccessTest(self):
		with open('Tests/SuccessTests.txt', 'r') as file:
			print('Success tests:\n')
			for line in file:
				ster = line.replace('\n', '')
				os.system(name + " " + ster)

			print('\n--------------------------------\n')

	def ErrorTest(self):
		with open('Tests/ErrorTests.txt', 'r') as file:
			print('Error tests:\n')
			for line in file:
				ster = line.replace('\n', '')
				os.system(name + " " + ster)
			print('\n--------------------------------\n')


name = sys.argv[1]
tt = TestLab()
tt.SuccessTest()
tt.ErrorTest()
