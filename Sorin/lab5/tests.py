import unittest
import subprocess


class tester(unittest.TestCase):

	def test1(self):
		with open('./Tests/test_1.txt', 'r') as file:
			print('\nenter', file.readlines())
			res = '\x1b[2J\x1b[HNumber of element meetings: 0\nElement added\n\n|-1|-1|-1| 0|-1|\n\n|-1|      abc0|ex0|\n\n\x1b[2J\x1b[HNumber of element meetings: 0\nElement added\n\n|-1|-1|-1| 0| 1|\n\n|-1|      abc0|ex0|\n|-1|      abc1|ex1|\n\n\x1b[2J\x1b[HNumber of element meetings: 0\nElement added\n\n| 2|-1|-1| 0| 1|\n\n|-1|      abc0|ex0|\n|-1|      abc1|ex1|\n|-1|      abc2|ex2|\n\n\x1b[2J\x1b[HNumber of element meetings: 0\nElement added\n\n| 2| 3|-1| 0| 1|\n\n|-1|      abc0|ex0|\n|-1|      abc1|ex1|\n|-1|      abc2|ex2|\n|-1|      abc3|ex3|\n\n\x1b[2J\x1b[HNumber of element meetings: 0\nElement added\n\n| 2| 3| 4| 0| 1|\n\n|-1|      abc0|ex0|\n|-1|      abc1|ex1|\n|-1|      abc2|ex2|\n|-1|      abc3|ex3|\n|-1|      abc4|ex4|\n\n'



			self.assertEqual(subprocess.check_output(["./lab5"], universal_newlines=True), res)
			print(res)
	def test2(self):
		with open('./Tests/test_2.txt', 'r') as file:
			print('\nenter', file.readlines())
			res = 'Error while entering expression'



			self.assertEqual(subprocess.check_output(["./lab5"], universal_newlines=True), res)
			print(res)		
	def test3(self):
		with open('./Tests/test_3.txt', 'r') as file:
			print('\nenter', file.readlines())
			res = '\x1b[2J\x1b[HNumber of element meetings: 0\nElement added\n\n| 0|-1|-1|-1|-1|\n\n|-1|         5|s0|\n\n\x1b[2J\x1b[HNumber of element meetings: 1\nElement added\n\n| 0|-1|-1|-1|-1|\n\n| 1|         5|s0|\n|-1|         5|s1|\n\n\x1b[2J\x1b[HNumber of element meetings: 2\nElement added\n\n| 0|-1|-1|-1|-1|\n\n| 1|         5|s0|\n| 2|         5|s1|\n|-1|         5|s2|\n\n'



			self.assertEqual(subprocess.check_output(["./lab5"], universal_newlines=True), res)
			print(res)
			
	
								
if __name__ == '__main__':
	unittest.main()				
	
