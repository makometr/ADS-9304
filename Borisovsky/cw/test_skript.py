import unittest
import subprocess

 
class tester(unittest.TestCase):

	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', ' ')
				print("Input: ", s)
				arguments = []
				arguments = s.split('_')
				self.assertIn('success', subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True) + '\n')

	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', ' ')
				print("Input: ", s)
				arguments = []
				arguments = s.split('_')
				self.assertIn('Wrong expression', subprocess.check_output(["./cw"], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./cw"], universal_newlines=True) + '\n')
	

	def test3(self):
		with open('./Tests/test3.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', ' ')
				print("Input: ", s)
				arguments = []
				arguments = s.split('_')
				self.assertIn('success', subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True) + '\n')
	
	def test4(self):
		with open('./Tests/test4.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', ' ')
				print("Input: ", s)
				arguments = []
				arguments = s.split('_')
				self.assertIn('You entered an invalid character.', subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True) + '\n')

	def test5(self):
		with open('./Tests/test5.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', ' ')
				print("Input: ", s)
				arguments = []
				arguments = s.split('_')
				self.assertIn('wrong string', subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True))		
				print("Output:", end = ' ')
				print(subprocess.check_output(["./cw", arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]], universal_newlines=True) + '\n')


	
	

	
	
if __name__ == '__main__':
	unittest.main()
