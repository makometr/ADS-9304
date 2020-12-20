import unittest
import subprocess


class tester(unittest.TestCase):

	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('success', subprocess.check_output(["./lab5", s], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./lab5", s], universal_newlines=True) + '\n')


	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('wrong string\n', subprocess.check_output(["./lab5", s], universal_newlines=True))
				print("Output:", end = ' ')
				print("wrong string\n")

	
	
if __name__ == '__main__':
	unittest.main()
