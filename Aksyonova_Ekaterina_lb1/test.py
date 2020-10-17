#!/usr/bin/python3
import os
 
test = { "TRUE" : "The string is correct",
        "A": "The string is correct",
        "NOT NOT NOT NOT A": "The string is correct",
        "(TRUE AND FALSE)": "The string is correct",
        "TRUE AND NOT A": "The string is not correct",
        "(NOT A)": "The string is not correct",
        "NOT     FALSE": "The string is correct",
        "(NOT AND NOT NOT NOT A)": "The string is not correct",
        "False": "The string is not correct",
        "NOT (NOT NOT FALSE OR NOT NOT NOT A)": "The string is correct",
        "(NOT A AND FALSE": "The string is not correct",
        "( FALSE AND TRUE )": "The string is not correct",
        "NOT A AND TRUE)": "The string is not correct",
        "( AND )": "The string is not correct"
        }
 
os.system("g++ ./Source/lab.cpp -o lab")
os.system('touch result.txt')
 
for str in test.keys():
    os.system("./lab \"{}\" > result.txt".format(str))
    file = open('result.txt', 'rt')
    res = file.read().split('\n')[0]

    if res == test.get(str):
        print("{} - correct".format(res))
    else:
        print("{} - wrong".format(res))
    file.close()
 
os.system('rm -rf result.txt')
