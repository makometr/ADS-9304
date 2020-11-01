import unittest
import subprocess


class tester(unittest.TestCase):
	
	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Correct!\n', subprocess.check_output(["./lab2", s], universal_newlines=True))
				res = ''
				for i in s:
					if i != '(' and i != ')':
						res += i		
				print("Output: ")
				print(res)
				print("Correct!")
				

	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				print("Input: ", s)
				self.assertIn('Wrong expression!\n', subprocess.check_output(["./lab2", s], universal_newlines=True))
				print("Output: ")
				print("Wrong expression!\n")

if __name__ == '__main__':
	unittest.main()
