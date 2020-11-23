#!/usr/bin/python3
import unittest
import subprocess

class script(unittest.TestCase):
	def testCorrect(self):
		print()
		with open('./tests/test.txt', 'r') as file:
			for line in file:
				res = subprocess.check_output(["./lab4", line], universal_newlines = True).split('\n')
				programResult = res[-3][res[-3].find('[') : res[-3].find(']') + 1]
				realResult = res[-2][res[-2].find('[') : res[-2].find(']') + 1]
				print("Program output:", programResult)
				print("Correct output:", realResult)
				print()
				self.assertEqual(programResult, realResult)

	def testError(self):
		print()
		with open('./tests/error.txt', 'r') as file:
			for line in file:
				res = subprocess.check_output(["./lab4", line], universal_newlines = True)
				res = ''.join(res.split('\n'))
				print("Program output:", res)
				print("Correct output: Error: wrong input string")
				print()
				self.assertIn("Error", res)

if __name__ == '__main__':
	unittest.main()
