import sys
import os

print("Make sure that this script is in the same directory as the program execute file.\n")
if not os.path.isfile("testScript.conf"):
    f = open("testScript.conf", mode = 'w')
    f.write("ProgramName=\n")
    f.write("DirNameOfTests=\n")
    f.write("NameOfTestFile=\n")
    f.write("AmountOfTests=\n")
    f.write("DirNameOfAnswers=\n")
    f.write("NameOfAnswerFile=")
    f.close()
    print("Please fill the config file")
else:
    sys.stdin = open("testScript.conf", mode = 'r')
    programName = input()[len("programName=")::]
    testDir = input()[len("DirNameOfTests=")::] + '/'
    testName = input()[len("NameOfTestFile=")::]
    amountOfTests = int(input()[len("AmountOfTests=")::])
    correctAnsDir = input()[len("DirNameOfAnswers=")::] + '/'
    correctAnsName = input()[len("NameOfAnswerFile=")::]
    sys.stdin.close()

    if not os.path.isdir(testDir + "ProgramAns/"):
        os.mkdir(testDir + "ProgramAns/")
    else:
        os.system("rm -f -R " + testDir + "ProgramAns/testAns?*")
    ansDirInTestDir = "ProgramAns/"
    ansName = "testAns"
    amountOfFails = 0
    amountOfSuccesses = 0
    for i in range(0, amountOfTests):
        fil = open(testDir + testName + str(i))
        inputData = fil.readline()
        os.system("./" + programName + ' ' + inputData + " > " + testDir + ansDirInTestDir + ansName + str(i) + "\n")

        sys.stdin = open(testDir + ansDirInTestDir + ansName + str(i), mode = 'r')
        answer = input()
        sys.stdin.close()

        sys.stdin = open(testDir + correctAnsDir + correctAnsName + str(i), mode = 'r')
        correctAnswer = input()
        sys.stdin.close()


        print(testName + str(i) + ":\nInput: " + inputData + "\nCorrectAnswer: " + correctAnswer + "\nAnswer: " + answer + "\nResult: ", end = "")
        if answer == correctAnswer:
            amountOfSuccesses += 1
            print("success")
        else:
            amountOfFails += 1
            print("fail")
        print('\n', end = '')
    print("Total: Successes: " + str(amountOfSuccesses) + ". Fails: " + str(amountOfFails))
