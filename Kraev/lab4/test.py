
import unittest
import subprocess		
		

class TestLab1(unittest.TestCase):

	def test1(self):
		with open('Tests/test1.txt', 'r') as file:
			text = file.read();
			print("./lab \"2 111 5 0 4 7 9 12 6\" \n")
			subprocess.call(["./lab", "2 111 5 0 4 7 9 12 6"])
			self.assertEqual(subprocess.check_output(["./lab", "2 111 5 0 4 7 9 12 6"]), text)
	
	def test2(self):
		with open('Tests/test2.txt', 'r') as file:
			text = file.read();
			print("\n\n./lab \"1 6 9 a 3 5 2 g\"\n")
			subprocess.call(["./lab", "1 6 9 a 3 5 2 g"])
			self.assertEqual(subprocess.check_output(["./lab", "1 6 9 a 3 5 2 g"]), text)


	def test3(self):
		with open('Tests/test3.txt', 'r') as file:
			text = file.read();
			print("\n\n./lab \"9 8 7 6 5 4 3 2 1\"\n")
			subprocess.call(["./lab", "9 8 7 6 5 4 3 2 1"])
			self.assertEqual(subprocess.check_output(["./lab", "9 8 7 6 5 4 3 2 1"]), text)

	def test4(self):
		with open('Tests/test4.txt', 'r') as file:
			text = file.read();
			print("\n\n./lab \"1000 2000 100 60 4 111111 5555 88 66\n")
			subprocess.call(["./lab", "1000 2000 100 60 4 111111 5555 88 66"])
			self.assertEqual(subprocess.check_output(["./lab", "1000 2000 100 60 4 111111 5555 88 66"]), text)

	def test5(self):
		with open('Tests/test5.txt', 'r') as file:
			text = file.read();
			print("\n\n./lab \"9 7 5 3 1 9 7 5 3 1 9 7 5 3 1\n")
			subprocess.call(["./lab", "9 7 5 3 1 9 7 5 3 1 9 7 5 3 1"])
			self.assertEqual(subprocess.check_output(["./lab", "9 7 5 3 1 9 7 5 3 1 9 7 5 3 1"]), text)

if __name__ == '__main__':
	unittest.main()

