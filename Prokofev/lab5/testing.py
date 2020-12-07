import unittest
import subprocess
import os	


class TestLab5(unittest.TestCase):

	def SuccessTest(self):
		with open('Tests/SuccessTests.txt', 'r') as file:
			print('Success tests:\n')
			for line in file:
				ster = line.replace('\n', '')
				os.system("./lab5 " + ster)

			print('\n--------------------------------\n')


tt = TestLab5()
tt.SuccessTest()
