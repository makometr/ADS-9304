import unittest
import subprocess


class tester(unittest.TestCase):
	
	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				res = ""
				res = res + line
				res = res + "It is bracket!\n"
				s = line.replace('\n', '')
				self.assertEqual(subprocess.check_output(["./lab1", s], universal_newlines=True), res)

	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				self.assertIn('It is not bracket!\n', subprocess.check_output(["./lab1", s], universal_newlines=True))

if __name__ == '__main__':
	unittest.main()
