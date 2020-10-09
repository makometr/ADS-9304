import os

number_of_tests = 27
exec_file = './lab1'
path_to_tests = 'Tests/tests/test_'
path_to_answers = 'Tests/answers/answers_'
path_to_correct_answers = 'Tests/correct_answers/answers_'
exp = '.txt'

for i in range(number_of_tests):
    num = i + 1
    os.system(
        f'{exec_file} {path_to_tests}{num}{exp} > {path_to_answers}{num}{exp}')

    ans_1 = open(f'{path_to_correct_answers}{num}{exp}').readline().rstrip('\n')
    ans_2 = open(f'{path_to_answers}{num}{exp}').readline().rstrip('\n')
    str_test = open(f'{path_to_tests}{num}{exp}').readline()

    print(f'test_{num}:\n  string: {str_test}\n  answer: {ans_1}\n  result: ', end='')
    if ans_1 == ans_2:
        print(f'correct')
    else:
        print(f'incorrect')
