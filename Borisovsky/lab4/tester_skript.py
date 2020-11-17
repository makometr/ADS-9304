import unittest
import subprocess


class tester(unittest.TestCase):

	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				arguments = []
				arguments = s.split(' ')
				self.assertIn('sorting spent', subprocess.check_output(["./lab4", arguments[0], arguments[1]], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./lab4", arguments[0], arguments[1]], universal_newlines=True) + '\n')

	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				arguments = []
				arguments = s.split(' ')
				self.assertIn('no such key', subprocess.check_output(["./lab4", arguments[0], arguments[1]], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./lab4", arguments[0], arguments[1]], universal_newlines=True) + '\n')
	

	def test3(self):
		with open('./Tests/test3.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				arguments = []
				arguments = s.split(' ')
				self.assertIn('you did not specify', subprocess.check_output(["./lab4", arguments[0], arguments[1]], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./lab4", arguments[0], arguments[1]], universal_newlines=True) + '\n')
	
	

	
	
if __name__ == '__main__':
	unittest.main()
