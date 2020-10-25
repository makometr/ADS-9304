import subprocess

ans = [
    "Binsearch:\tYes\nPyramid:\tYes\n;B+P+", #1
    "Binsearch:\tYes\nPyramid:\tYes\n;B+P+", #2
    "Binsearch:\tYes\nPyramid:\tNo\n;B+P-", #3
    "Binsearch:\tNo\nPyramid:\tYes\n;B-P+", #4
    "Binsearch:\tNo\nPyramid:\tYes\n;B-P+", #5
    "ERROR: given string tree is invalid;INV_ARG", #6
    "ERROR: given string tree is invalid;INV_ARG", #7
    "Binsearch:\tNo\nPyramid:\tYes\n;B-P+", #8
    "Binsearch:\tYes\nPyramid:\tNo\n;B+P-", #9
    "ERROR: given strig tree is invalid;INV_ARG", #10
]

counter = 0
for i in range(1, 11):
    f = open(f"Tests/test{i}.txt", 'r')
    inp = f.read().split()
    trueRes = ans[i-1].split(';')
    print(f"Starting test{i}:", f"[{inp}] -> [{trueRes[1]}]")
    f.close()
    f = open(f"Tests/testres{i}.txt", 'r')
    myRes = f.read()
    f.close()
    if myRes == trueRes[0]:
        print(f"\033[32mtest{i} completed successfully\033[m\n")
        counter+=1
    else:
        print(f"\033[31mtest{i} failed:\033[m", \
            f"your res = [{myRes}]", \
                f"true res = [{trueRes[1]}]", sep='\n', end='\n')
print("\033[32m" if counter == 10 else  "\033[31m" ,f"{counter}/10 tests completed successfully\033[m\n")
