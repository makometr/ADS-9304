import unittest
import subprocess


class tester(unittest.TestCase):

	def test1(self):
		with open('./Tests/test_1.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "These are brackets\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)
			
	def test2(self):
		with open('./Tests/test_2.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "These are brackets\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)
			
	def test3(self):
		with open('./Tests/test_3.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "These are brackets\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)
	
	def test4(self):
		with open('./Tests/test_4.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "Error while entering expression\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)
	
	def test5(self):
		with open('./Tests/test_5.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "Missed space\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)
	
	def test6(self):
		with open('./Tests/test_6.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "Missed \'A\', \'B\' or \'(\'\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)
	
	def test7(self):
		with open('./Tests/test_7.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "Missed \')\'\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)
	
	def test8(self):
		with open('./Tests/test_8.txt', 'r') as file:
			print('\nenter', file.readline())
			res = "These are brackets\n"
						
			self.assertEqual(subprocess.check_output(["./lab1"], universal_newlines=True), res)
			print(res)	
			
	
		
		
													
							
if __name__ == '__main__':
	unittest.main()				
