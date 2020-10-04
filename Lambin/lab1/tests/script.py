#!/usr/bin/python3
import os

test = { "true and false" : "FALSE",
         "false or true" : "TRUE",
         "true and (false or true)" : "TRUE",
         "true and (true and (true and (true and false)))" : "FALSE",
         "   true    and   false or (  false  or  false   )    " : "FALSE",
         "TRUE AND (FALSE OR TRUE) OR (TRUE AND FALSE)" : "TRUE",
         "TrUe Or FaLsE aNd TrUe" : "TRUE" }

os.system("g++ ../source/lab1.cpp -o lab1")
os.system('touch result.txt')

for str in test.keys():
    os.system("./lab1 \"{}\" > result.txt".format(str))
    file = open('result.txt', 'rt')
    res = file.read().split('\n')[0]

    if res.split(' ')[-1] == test.get(str):
        print("{} - correct".format(res))
    else:
        print("{} - wrong".format(res))
    file.close()

os.system('rm -rf result.txt lab1')
