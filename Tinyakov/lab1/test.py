import unittest
import subprocess
import os

class TestParamAnalyzer(unittest.TestCase):
    
    cwd = os.getcwd();

    def test_0_basic(self):    
        subtests = [ 
                    ['AAA = 15', "AAA=15\nCorrect.\n\n"],
                    ['AA4 = 23','AA4\nIncorrect. Name Error: Invalid name, character \'4\' is not letter.\n\n'],
                    ['AAw = 2P','AAw=2P\nIncorrect. Parameter Error: Invalid define, character \'P\' is not digit.\n\n'],
                    ['BBB=   \n    (RRR    =\n56)', "BBB=(RRR=56)\nCorrect.\n\n"],
                    ['AAA = BBB = 45','AAA=B\nIncorrect. Parameter Error: Invalid define, character \'B\' is not digit.\n\n'],
                    ['AAA = (BBB = 13)','AAA=(BBB=13)\nCorrect.\n\n'],
                    ['AAA = (BBB = 13','AAA=(BBB=13\nIncorrect. Parameter Error: Expected character \')\', but end of input were reached.\n\n'],
                    ['AAA = (BBB = 1','AAA=(BBB=1\nIncorrect. Parameter Error: Invalid define, expected digit, but end of input were reached.\n\n'],
                    ['AAA\n=    14)','AAA=14)\nIncorrect. List of parameters Error: Expected character \',\', but were given \')\'.\n\n'],
                    ['AAA\n=    14o','AAA=14o\nIncorrect. List of parameters Error: Expected character \',\', but were given \'o\'.\n\n'],
                    ['AAA\n=    14,','AAA=14,\nIncorrect. Name Error: Invalid name, excepted letter, but end of input were reached.\n\n'],
                    ['AAA  14','AAA1\nIncorrect. Parameter Error: Expected character \'=\', but were given \'1\'.\n\n'],
                    ['AAA  ','AAA\nIncorrect. Parameter Error: Expected character \'=\', but end of input were reached.\n\n']
                   ]
        
        for test in subtests:
            with open('input', 'w') as f:
                f.write(test[0])
            p = subprocess.run(['./lab1','input','output'], cwd = self.cwd)
            with open('output', 'r') as f:
                line = f.read()
                self.assertEqual(line, test[1])
    
    def test_1(self):
        subtests = [ 
                    ['AAA = 15   ,   BBB =   (AaA = (AAA = (AAA = 12)), FFF =10)\n','AAA=15,BBB=(AaA=(AAA=(AAA=12)),FFF=10)\nCorrect.\n\n'],
                    ['AAA = 15   ,   BBB =   (AaA = (AAA = (AAA = 12))), FFF =10\n','AAA=15,BBB=(AaA=(AAA=(AAA=12))),FFF=10\nCorrect.\n\n'],
                    ['AAA = 15   ,   BBB =   (AaA = (AAA = (AAA = 12))), FFF =10)\n','AAA=15,BBB=(AaA=(AAA=(AAA=12))),FFF=10)\nIncorrect. List of parameters Error: Expected character \',\', but were given \')\'.\n\n'],
                    ['AAA = 15   ,   BBB =   (AaA = (AAA = (AAA = 12)), FFF =10\n','AAA=15,BBB=(AaA=(AAA=(AAA=12)),FFF=10\nIncorrect. Parameter Error: Expected character \')\', but end of input were reached.\n\n'],
                    ['AAA = 15   ,   BBB =   AaA = AAA = AAA = 12, FFF =10\n','AAA=15,BBB=A\nIncorrect. Parameter Error: Invalid define, character \'A\' is not digit.\n\n'],
                   ]
        
        for test in subtests:
                with open('input', 'w') as f:
                    f.write(test[0])
                p = subprocess.run(['./lab1','input','output'], cwd = self.cwd)
                with open('output', 'r') as f:
                    line = f.read()
                    self.assertEqual(line, test[1])

    def test_2(self):
        subtests = [
                    ['Ssf = (AOE = 12,\n       FWA = 14,\n       ASF = 16,\n       VER = 20\n       ),\nFFF = 04, QWE=(AFA = (aas = 13,\n    vsd = ( yet = (faw = ( ker = ( ort = 95, not = 00,\n    trr = ( zzz = (kkk = (uuu = 14)))))))))','Ssf=(AOE=12,FWA=14,ASF=16,VER=20),FFF=04,QWE=(AFA=(aas=13,vsd=(yet=(faw=(ker=(ort=95,not=00,trr=(zzz=(kkk=(uuu=14)))))))))\nCorrect.\n\n'],
                    ['asd = 00, fbk = 11, AAA = (OOO = 13),\nFFF = 12, BBB = 94, QQQ  = 93, KKK = 21,\nMMM = 21, NNN = 21, DDD = (EEE = (kad = 94)),\nDDD  = 64, VVV = 82,HHH=65, LLL = 08, ret = 42','asd=00,fbk=11,AAA=(OOO=13),FFF=12,BBB=94,QQQ=93,KKK=21,MMM=21,NNN=21,DDD=(EEE=(kad=94)),DDD=64,VVV=82,HHH=65,LLL=08,ret=42\nCorrect.\n\n']
                   ]

        for test in subtests:
                with open('input', 'w') as f:
                    f.write(test[0])
                p = subprocess.run(['./lab1','input','output'], cwd = self.cwd)
                with open('output', 'r') as f:
                    line = f.read()
                    self.assertEqual(line, test[1])

    def test_3(self):
        p = subprocess.run(['./lab1','input'], cwd = self.cwd, stdout = subprocess.PIPE)
        self.assertEqual(p.returncode, 1);
        p = subprocess.run(['./lab1','non_exist_file','output'], cwd = self.cwd, stdout = subprocess.PIPE)
        self.assertEqual(p.returncode, 2);

    def tearDown(self):
        if os.path.isfile('./input'):
            os.remove('./input')
        if os.path.isfile('./output'):
            os.remove('./output')
        
if __name__ == "__main__":
    unittest.main()
