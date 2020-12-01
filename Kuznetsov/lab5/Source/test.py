myRes = list(map(int, input().strip().split(' ')))
inputSeq = list(map(int, input().strip().split(' ')))
print(f'Testing sequence {inputSeq}', f'My program res: {myRes}', sep='\n')
trueRes = sorted(inputSeq)
if myRes == trueRes:
    print('\033[32mCompleted successfully\033[m\n')
else:
    print('\033[31mA failure occured\033[m\n', f'True program res: {trueRes}', sep='\n')
