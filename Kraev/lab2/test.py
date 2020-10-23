
import unittest
import subprocess		
from subprocess import check_call, STDOUT

class TestLab1(unittest.TestCase):

	def testAdd(self):
		a = open('Tests/test1.txt', 'r')
		str = a.read()
		print('./lab -a \"5 part 5 [qwerty]\" ')
		print(subprocess.check_output(["./lab", "-a", "5 part 5 [qwerty] "]))
		self.assertEqual(subprocess.check_output(["./lab", "-a", "5 part 5 [qwerty] "]),str)
	
	def testDeleteName(self):
		a = open('Tests/test2.txt', 'r')
		print('./lab -c \" chapter 1 \"')
		str = a.read()
		print(subprocess.check_output(["./lab", "-c", " chapter 1 "]))
		self.assertEqual(subprocess.check_output(["./lab", "-c", " chapter 1 "]), str)

	def testDeleteNum(self):
		a = open('Tests/test3.txt', 'r')
		print('./lab -b \"1.2\"')
		str = a.read()
		print(subprocess.check_output(["./lab", "-b", "1.2"]))
		self.assertEqual(subprocess.check_output(["./lab", "-b", "1.2"]),str)

	def testChangeName(self):
		a=open('Tests/test4.txt', 'r')
		print('./lab -d \"1.1\" \"Hello\"')
		str = a.read()
		print(subprocess.check_output(["./lab", "-d", "1.1", " Hello "]))
		self.assertEqual(subprocess.check_output(["./lab", "-d", "1.1", " Hello "]),str)

	def testChangeNum(self):
		a=open('Tests/test5.txt', 'r')
		print('./lab -e \"1.1\" \"2.2\"')
		str = a.read()
		print(subprocess.check_output(["./lab", "-e", "1.1", "2.2"]))
		self.assertEqual(subprocess.check_output(["./lab", "-e", "1.1", "2.2"]),str)

if __name__ == '__main__':
	unittest.main()
