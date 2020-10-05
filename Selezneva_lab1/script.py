#!/usr/bin/python3
import os

test = { "12.3" : "The real number",
	     "12.-3" : "This is not real number",
	     "+12.3" : "The real number",
	     "12E-1" : "The real number",
	     "12E.1" : "This is not real number",
	     "12E12." : "This is not real number",
	     "+12.3E1" : "The real number",
	     ".12" : "This is not real number",
	     "E12" : "This is not real number",
	     "+12.-3E1" : "This is not real number",
	     "gjhgj679" : "This is not real number",}

os.system("g++ a_ds_1.cpp -o a_ds_1")
os.system('touch result.txt')

for str in test.keys():
    os.system("./a_ds_1 \"{}\" > result.txt".format(str))
    file = open('result.txt', 'rt')
    res = file.read().split('\n')[0]

    if res == test.get(str):
        print("{} - correct".format(res))
    else:
        print("{} - wrong".format(res))
    file.close()

os.system('rm -rf result.txt a_ds_1')
