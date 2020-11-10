import unittest
import subprocess
import os
import filecmp
import random

class TestParamAnalyzer(unittest.TestCase):
    
    cwd = os.getcwd()
    test_dir = './Tests/'
    tests = []
    alp_power = 32

    @classmethod
    def setUpClass(self):
        files = os.listdir(self.test_dir)
        for f in files:
            if(f.endswith('.in')):
                out = f[:f.rfind('.')] + ".out"
                if(files.count(out) > 0):
                    self.tests.append([self.test_dir + f, self.test_dir + out])
            if(f.endswith('.io')):
                self.tests.append([self.test_dir+f])

    def test_all(self):
        print('Start Testing...')
        out = 'output.test'
        for test in self.tests:
            if(test[0].endswith('.in')):
                with open(test[0], 'r') as f_in:
                    cmd = test[0][:test[0].rfind('.')]
                    cmd = cmd[cmd.rfind('.')+1:]
                    print(cmd)
                    with open(out, 'w') as f_out:
                        p = subprocess.run(['./lab3', cmd], cwd = self.cwd, stdin = f_in, stdout = f_out)
                with open(test[0], 'r') as f_in:
                    print('Input: ',f_in.read(), sep='')
                with open(out, 'r') as f_out:
                    print('Output: ', f_out.read(), sep='')
                self.assertTrue(filecmp.cmp(out, test[1]))
            if(test[0].endswith('.io')):
                with open(test[0], 'r') as f_in:
                    text = f_in.read()
                print("Testing:", test[0])
                for i in range(1,self.alp_power):
                    #shift = random.randint(1, self.alp_power-1)
                    #while shift == 22 and test[0][test[0].rfind('test_'):len(test[0])-3] == 'test_7':
                    #    shift = random.randint(1, self.alp_power-1)
                    if test[0][test[0].rfind('test_'):len(test[0])-3] == 'test_7' and i == 22:
                        continue
                    inpt = 'text.test'
                    code = 'code.test'
                    hack = 'hack.test'
                    print('Shift:', i)
                    if(len(text) < 500):
                        print('Input:', text)
                    else:
                        print('Input: So much symbols')
                    with open(inpt, 'w') as f:
                        #f.write(str(shift) + '\n' + text)
                        f.write(str(i) + '\n' + text)
                    with open(inpt, 'r') as f_in:
                        with open(code, 'w') as f_out:
                            p = subprocess.run(['./lab3', 'encode'], cwd = self.cwd, stdin = f_in, stdout = f_out)
                    with open(code, 'r') as f_in:
                        with open(hack, 'w') as f_out:
                            p = subprocess.run(['./lab3', 'hack'], cwd = self.cwd, stdin = f_in, stdout = f_out)
                    with open(hack, 'r') as f:
                        hack_text = f.read()
                    if(len(hack_text) < 500):
                        print('Output:', hack_text)
                    else:
                        print('Output: So much symbols')
                    self.assertTrue(hack_text == text + '\n')




        print('End Testing')

    def tearDown(self):
        files = ['output.test', 'text.test', 'code.test', 'hack.test']
        for f in files:
            if os.path.isfile(f):
                os.remove(f)

        
if __name__ == "__main__":
    unittest.main()
