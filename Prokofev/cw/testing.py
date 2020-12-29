import unittest
import subprocess
import os
import sys


class TestLab(unittest.TestCase):

	def SuccessTest(self):
		with open('Tests/SuccessTests.txt', 'r') as file:
			print('\nSuccess tests:\n')
			while True:
				ln = file.readline()
				ln2 = file.readline()
				ln3 = file.readline()
				ln4 = file.readline()
				fl = open('input.txt', 'w')
				fl.write(ln)
				fl.write(ln2)
				fl.write(ln3)
				fl.write(ln4)
				fl.close()
				os.system(name)
				print('\n--------------------------------\n')
				d = file.readline()
				if not d:
					break



name = sys.argv[1]
tt = TestLab()
tt.SuccessTest()
