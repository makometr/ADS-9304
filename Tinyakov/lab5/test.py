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
        arr = []
        for i in range(self.size):
            arr.append(random.randint(0, 1024))
            input_str += str(arr[-1]) + ' '
        print('List size:', self.size)
        print("List for search: [ ", input_str, ']', sep='')
        output_str = ''
        arr = list(dict.fromkeys(arr))
        for i in sorted(arr):
            output_str += str(i) + ' ';
        input_str = str(self.size) + '\n' + input_str
        finded = []
        for i in range(0, self.search_count):
            search_element = random.randint(0, 1024)
            while search_element in finded:
                search_element += 1
            finded.append(search_element)
            print("Search element:", search_element)
            in_str = input_str + '\n' + str(search_element)
            check_str = output_str + '\nCount of element: ' + str(arr.count(search_element)) + '\n'
            with open(out, 'w') as f_out:
                p = subprocess.run(['./lab5', ], cwd = self.cwd, stdout = f_out, text = True, input = in_str)
            with open(out, 'r') as f_out:
                str_out = f_out.read()
            str_out = str_out[str_out.rfind('\n', 0, (str_out.rfind('\nCount') - 1)) + 1:]
            print('Output:', str_out, sep='\n')
            print('Correct output:', check_str, sep='\n')
            self.assertTrue(str_out == check_str)

    def test_1(self):
        self.size = 25
        self.search_count = 25
        self.start_test()

    def test_2(self):
        self.size = 73
        self.search_count = 25
        self.start_test()

    def test_3(self):
        self.size = 549
        self.search_count = 25
        self.start_test()

    def test_4(self):
        self.size = 1091
        self.search_count = 25
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
