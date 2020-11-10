import unittest
import subprocess
import os
import filecmp

class TestParamAnalyzer(unittest.TestCase):
    
    cwd = os.getcwd()
    test_dir = './Tests/'
    tests = []

    @classmethod
    def setUpClass(self):
        files = os.listdir(self.test_dir)
        for f in files:
            if(f.endswith('.in')):
                out = f[:f.rfind('.')] + ".out"
                if(files.count(out) > 0):
                    self.tests.append([self.test_dir + f, self.test_dir + out])

    def test_all(self):
        print('Start Testing...')
        out = 'output.test'
        for test in self.tests:
            with open(test[0], 'r') as f_in:
                with open(out, 'w') as f_out:
                    p = subprocess.run(['./lab2',], cwd = self.cwd, stdin = f_in, stdout = f_out)
            with open(test[0], 'r') as f_in:
                print('Input: ',f_in.read(), sep='')
            with open(out, 'r') as f_out:
                print('Output: ', f_out.read(), sep='')
            self.assertTrue(filecmp.cmp(out, test[1]))
        #    if os.path.isfile(out):
        #        os.remove(out)
        print('End Testing')

    def tearDown(self):
        out = 'output.test'
        if os.path.isfile(out):
            os.remove(out)

        
if __name__ == "__main__":
    unittest.main()
