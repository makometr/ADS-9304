#!/usr/bin/python3
import os
import subprocess

correct = { '0 2' : ['0 Preambule - Book II ', 
                     '\t0.0 Chapter 1 ', 
                     '\t\t0.0.0 Subchapter 1 \"Title of the first subchapter\"', 
                     '\t\t0.0.1 Subchapter 2 \"Title of the second subchapter\"', 
                     '1 Book I ', 
                     '\t1.0 Chapter 1 \"Title of the first chapter\"', 
                     '\t1.1 Chapter 2 \"Title of the second chapter\"', 
                     '\t1.2 Chapter 3 \"Title of the third chapter\"', 
                     '2 Epilogue '],
        '1.3 1.1' : ['0 Preambule ', 
                     '1 Book I ', 
                     '\t1.0 Chapter 1 - Chapter 3 \"Title of the first chapte. Title of the third chapter\"', 
                     '\t1.1 Chapter 2 \"Title of the second chapter\"', 
                     '2 Book II ', 
                     '\t2.0 Chapter 1 ', 
                     '\t\t2.0.0 Subchapter 1 \"Title of the first subchapter\"', 
                     '\t\t2.0.1 Subchapter 2 \"Title of the second subchapter\"', 
                     '3 Epilogue '],
    '2.1.1 2.1.2' : ['0 Preambule ', 
                     '1 Book I ', 
                     '\t1.0 Chapter 1 \"Title of the first chapter\"', 
                     '\t1.1 Chapter 2 \"Title of the second chapter\"', 
                     '\t1.2 Chapter 3 \"Title of the third chapter\"', 
                     '2 Book II ', 
                     '\t2.0 Chapter 1 ', 
                     '\t\t2.0.0 Subchapter 1 - Subchapter 2 \"Title of the first subchapte. Title of the second subchapter\"', 
                     '3 Epilogue ']
         }

error = { '0 0' : 'Error: elements are equal',
          '1 4' : 'Error: no element with such number',
      '1.1 2.1' : 'Error: elements are not in one sublist',
    '2.1 2.1.1' : 'Error: elements are not in one sublist'
        }

print()
print('INPUT FILE:')
with open('./tests/test.txt', 'rt') as file:
    for line in file:
        print('\t{}'.format(line[0 : -1]))
print('\n_________\n')

count = 0
for str in correct.keys():
    count += 1
    os.system('./lab2 ./tests/test.txt \"{}\"'.format(str))
    flag = True
    print('INPUT:\n\t\"{}\"\n'.format(str))
    with open('result.txt', 'rt') as file:
        i = 0
        print('OUTPUT FILE: ')
        for line in file:
            print('\t{}'.format(line[0 : -1]))
            if line[0 : -1] != correct.get(str)[i]:
                flag = False
            i += 1
        print()
        if flag == True:
            print('Test {} - correct'.format(count))
        else:
            print('Test {} - incorrect'.format(count))
        if (count != 3):
            print('___\n')

print('_________\n')

os.system('touch err.txt')
count = 0
for str in error.keys():
    count += 1
    os.system('./lab2 ./tests/test.txt \"{}\" 2> err.txt'.format(str))
    print('INPUT:\n\t\"{}\"\n'.format(str))
    with open('err.txt', 'rt') as file:
        print('OUTPUT: ')
        for line in file:
            print('\t{}\n'.format(line[0 : -1]))
            if line[0 : -1] == error.get(str):
                print('Test {} - correct'.format(count))
            else:
                print('Test {} - incorrect'.format(count))
            print('___\n')
            break
os.system('rm -rf err.txt')
os.system('rm -rf result.txt')
