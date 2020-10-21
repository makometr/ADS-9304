
import unittest
import subprocess		


class TestLab1(unittest.TestCase):

	def testCorrect(self):
		with open('Tests/correct.txt', 'r') as file:
			for line in file:
				str = line.replace('\n', '')
				self.assertEqual(subprocess.check_output(["./lab1", str]), 'correct\n')
	
	def testIncorrect(self):
		with open('Tests/incorrect.txt', 'r') as file:
			for line in file:
				str = line.replace('\n', '')
				self.assertEqual(subprocess.check_output(["./lab1", str]), 'incorrect\n')

if __name__ == '__main__':
	unittest.main()

