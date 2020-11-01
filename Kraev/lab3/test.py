
import unittest
import subprocess		
from subprocess import check_call, STDOUT

class TestLab1(unittest.TestCase):

	def test1(self):
		self.assertEqual(subprocess.check_output(["./lab", "a(b)(c(d)(e))"]),"False\n")
		print("./lab \"a(b)(c(d)(e))\"\nFalse\n")
	
	def test3(self):
		self.assertEqual(subprocess.check_output(["./lab", "a(b)(b)asdsad"]),"ERROR: incorrect string\n")
		print("./lab \"a(b)(b)asdsad\"\nERROR: incorrect string\n")

	def test4(self):
		self.assertEqual(subprocess.check_output(["./lab", "a(b)(b(c))"]),"True\n")
		print("./lab \"a(b)(b(c))\"\nTrue\n")

	def test5(self):
		self.assertEqual(subprocess.check_output(["./lab", "a(b)(g)(h)"]),"ERROR: incorrect string\n")
		print("./lab \"a(b)(g)(h)\"\nERROR: incorrect string\n")

if __name__ == '__main__':
	unittest.main()
