import unittest
import subprocess


class tester(unittest.TestCase):
	
	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			for line in file:
				res = "Oh, YES, it's bracketed_text\n"
				s = line.replace('\n', '')
				res += s
				self.assertEqual(subprocess.check_output(["./lab1", s], universal_newlines=True), res)

	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			for line in file:
				s = line.replace('\n', '')
				self.assertIn('Error', subprocess.check_output(["./lab1", s], universal_newlines=True))

if __name__ == '__main__':
	unittest.main()
