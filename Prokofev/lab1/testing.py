import unittest
import subprocess		


class TestLab1(unittest.TestCase):

	def SuccessTest(self):
		with open('Tests/SuccessTests.txt', 'r') as file:
			for line in file:
				str = line.replace('\n', '')
				self.assertEqual(subprocess.check_output(["./lab1", str]), 'success\n')

	def ErrorTest(self):
		with open('Tests/ErrorTests.txt', 'r') as file:
			for line in file:
				str = line.replace('\n', '')
				self.assertEqual(subprocess.check_output(["./lab1", str]), 'error\n')

if __name__ == '__main__':
	unittest.main()