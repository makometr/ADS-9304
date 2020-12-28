import unittest
import subprocess


class tester(unittest.TestCase):
	
	def test1(self):
		with open('./Tests/test1.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))
	
	def test2(self):
		with open('./Tests/test2.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))

	def test3(self):
		with open('./Tests/test3.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))
	
	def test4(self):
		with open('./Tests/test4.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))

	def test5(self):
		with open('./Tests/test5.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))
	
	def test6(self):
		with open('./Tests/test6.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))

	def test7(self):
		with open('./Tests/test7.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))
	
	def test8(self):
		with open('./Tests/test8.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))

	def test9(self):
		with open('./Tests/test9.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))
	
	def test10(self):
		with open('./Tests/test10.txt', 'r') as file:
			l = file.readlines()
			l[0] = l[0].replace('\n', "")
			l[1] = l[1].replace('\n', "")
			l[2] = l[2].replace('\n', "")
			print("Input:\n")			
			print(l[0])
			print(l[1])
			print(l[2])
			self.assertIn('Finished successful!\n', subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))	
			print("\nOutput:\n")
			print(subprocess.check_output(["./cw", l[0], l[1], l[2]], universal_newlines=True))
	
if __name__ == '__main__':
	unittest.main()

