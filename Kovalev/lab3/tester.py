import unittest
import subprocess


class tester(unittest.TestCase):
	
	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Incorrect string!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))	
				print("Output: ")
				print("Incorrect string!")
				

	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Finished successful!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))
				print("Output: ")
				print("a b c ")
				print("Finished successful!")
	
	def test3(self):
		with open('./Tests/test3.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Incorrect string!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))	
				print("Output: ")
				print("Incorrect string!")
	
	def test4(self):
		with open('./Tests/test4.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Finished successful!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))
				print("Output: ")
				print("a b c e ")
				print("Finished successful!")
	
	def test5(self):
		with open('./Tests/test5.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Finished successful!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))
				print("Output: ")
				print("1 2 3 ")
				print("Finished successful!")
	
	def test6(self):
		with open('./Tests/test6.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Incorrect string!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))	
				print("Output: ")
				print("Incorrect string!")
	
	def test7(self):
		with open('./Tests/test7.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Incorrect string!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))	
				print("Output: ")
				print("Incorrect string!")
	
	def test8(self):
		with open('./Tests/test8.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Finished successful!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))
				print("Output: ")
				print("a b f d e g h ")
				print("Finished successful!")
	
	def test9(self):
		with open('./Tests/test9.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Incorrect string!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))	
				print("Output: ")
				print("Incorrect string!")
	
	def test10(self):
		with open('./Tests/test10.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Finished successful!\n', subprocess.check_output(["./lab3", s], universal_newlines=True))
				print("Output: ")
				print("1000 20 30 6 ")
				print("Finished successful!")

if __name__ == '__main__':
	unittest.main()
