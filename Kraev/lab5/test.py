import unittest
import subprocess		
		

class TestLab1(unittest.TestCase):

	def test1(self):
		subprocess.call(["./lab", "--encode", "Tests/codes.txt", "--file", "Tests/test.txt", "--out", "Tests/encoded_text.txt" ])
		subprocess.call(["./lab", "--decode", "Tests/codes.txt", "--file", "Tests/encoded_text.txt", "--out", "Tests/decoded_text.txt" ])
		with open("Tests/test.txt") as file:
			a = file.read()
		with open("Tests/decoded_text.txt") as file:
			b = file.read()
		with open("Tests/codes.txt") as file:
			c = file.read()
		print("./lab --encode Tests/codes.txt --file Tests/test.txt --out Tests/encoded_text.txt\n")
		print("./lab --decode Tests/codes.txt --file Tests/encoded_text.txt --out Tests/decoded_text.txt\n")
		print("Original text:\n")
		print(a)
		print('\nCodes:\n')
		print(c)
		print("\nDecoded text:\n")
		print(b)
		self.assertEqual(a, b+'\n')
	
	def test2(self):
		self.assertEqual(subprocess.check_output(["./lab"]), "ERROR: you must enable 1 of 2 modes\n")
		print("\n./lab\n")
		print("ERROR: you must enable 1 of 2 modes\n");

	def test3(self):
		 self.assertEqual(subprocess.check_output(["./lab", "--encode", "Tests/codes.txt"]), "ERROR: you must set output file\n")
		 print("\n./lab --encode Tests/codes.txt\n")
		 print("ERROR: you must set output file\n");

if __name__ == '__main__':
	unittest.main()

