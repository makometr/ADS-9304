import unittest
import subprocess


class tester(unittest.TestCase):

	def test1(self):
		with open('./Tests/tests/test1.txt', 'r') as file:
			line = file.readlines()
			print("\tTest 1\n")
			print("Input:\n")
			print(line[0])
			print(line[1])
			print(line[2])
			self.assertIn("Finished right", subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))
			
	def test2(self):
		with open('./Tests/tests/test2.txt', 'r') as file:
			line = file.readlines()
			print("\tTest 2\n")
			print("Input:\n")
			print(line[0])
			print(line[1])
			print(line[2])
			self.assertIn("Finished right", subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))
	def test3(self):
		with open('./Tests/tests/test3.txt', 'r') as file:
			print("\tTest 3\n")
			line = file.readlines()
			print("Input:\n")
			print(line[0])
			print(line[1])
			print(line[2])
			self.assertIn("Finished right", subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))
	def test4(self):
		with open('./Tests/tests/test4.txt', 'r') as file:
			print("\tTest 4\n")
			line = file.readlines()
			print("Input:\n")
			print(line[0])
			print(line[1])
			print(line[2])
			self.assertIn("Finished right", subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))
	def test5(self):
		with open('./Tests/tests/test5.txt', 'r') as file:
			line = file.readlines()
			print("\tTest 5\n")
			print("Input:\n")
			print(line[0])
			print(line[1])
			print(line[2])
			self.assertIn("Finished right", subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))
	def test6(self):
		with open('./Tests/tests/test6.txt', 'r') as file:
			line = file.readlines()
			print("\tTest 6\n")
			print("Input:\n")
			print(line[0])
			print(line[1])
			print(line[2])
			self.assertIn("Finished right", subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./lab5", line[0], line[1], line[2]], universal_newlines=True))
if __name__ == '__main__':
	unittest.main()
