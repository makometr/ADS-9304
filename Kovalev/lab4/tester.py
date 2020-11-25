import unittest
import subprocess


class tester(unittest.TestCase):
	
	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('\nSorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))	
				print("Output:\n\n")
		with open('./Tests/output1.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
				

	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))
				print("Output:\n\n")
		with open('./Tests/output2.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
				
	
	def test3(self):
		with open('./Tests/test3.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))	
				print("Output:\n\n")
		with open('./Tests/output3.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
	
	def test4(self):
		with open('./Tests/test4.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))
				print("Output:\n\n")
		with open('./Tests/output4.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
	
	def test5(self):
		with open('./Tests/test5.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))
				print("Output:\n\n")
		with open('./Tests/output5.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
	
	def test6(self):
		with open('./Tests/test6.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))	
				print("Output:\n\n")
		with open('./Tests/output6.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
	
	def test7(self):
		with open('./Tests/test7.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))	
				print("Output:\n\n")
		with open('./Tests/output7.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
	
	def test8(self):
		with open('./Tests/test8.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))
				print("Output:\n\n")
		with open('./Tests/output8.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
	
	def test9(self):
		with open('./Tests/test9.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))	
				print("Output:\n\n")
		with open('./Tests/output9.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)
	
	def test10(self):
		with open('./Tests/test10.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Sorting by Solomon:\n', subprocess.check_output(["./lab4", s], universal_newlines=True))
				print("Output:\n\n")
		with open('./Tests/output10.txt', 'r') as f:
			for line in f:
				s = line.replace('\n', '')
				print(s)

if __name__ == '__main__':
	unittest.main()

