import unittest
import subprocess
import os
import filecmp
import random

class TestParamAnalyzer(unittest.TestCase):
    
    cwd = os.getcwd()
    test_dir = './Tests/'
    tests = []

    @classmethod
    def setUpClass(self):
        print('Start Testing...')

    def start_test(self):
        out = 'output.test'
        check_out = 'check_output.test'
        in_file = 'input.test'
        input_str = ''
        for i in range(self.size):
            input_str += str(random.randint(0,1000000000)) + ' '
        print('List size:', self.size)
        print("List for search: [ ", input_str, ']', sep='')
        input_str = str(self.size) + '\n' + input_str
        for i in range(1, self.size+1):
            print("Search element on position:", i)
            in_str = input_str + '\n' + str(i) + '\n\n'
            with open(out, 'w') as f_out:
                p = subprocess.run(['./lab4', ], cwd = self.cwd, stdout = f_out, text = True, input = in_str)
            with open(check_out, 'w') as f_out:
                p = subprocess.run(['./check', ], cwd = self.cwd, stdout = f_out, text = True, input = in_str)
            with open(out, 'r') as f_out:
                str_out = f_out.read()
                print('Output:', str_out, sep='\n')
                str_out = str_out[str_out.rfind('K min ='):]
            with open(check_out, 'r') as f_out:
                str_check = f_out.read()
                print('Check output:', str_check, sep='\n')
                str_check = str_check[str_check.rfind('K min ='):]
            self.assertTrue(str_out == str_check)

    def test_0(self):
        out = 'output.test'
        in_str = '3\n42 666 13\n6\n\n'
        with open(out, 'w') as f_out:
            p = subprocess.run(['./lab4', ], cwd = self.cwd, stdout = f_out, text = True, input = in_str)
        with open(out, 'r') as f_out:
            output = f_out.read()
        self.assertTrue(output == 'Error: K > size\n')

    def test_1(self):
        self.size = 25
        self.start_test()

    def test_2(self):
        self.size = 73
        self.start_test()

    def test_3(self):
        self.size = 549
        self.start_test()

    #@unittest.skip('')
    def test_4(self):
        self.size = 1091
        self.start_test()

    def tearDown(self):
        files = []
        files.extend([f for f in os.listdir('./')
                    if f.endswith('.test')])
        for f in files:
            if os.path.isfile(f):
                os.remove(f)

        
if __name__ == "__main__":
    unittest.main()
