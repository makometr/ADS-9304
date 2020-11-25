import os

number_of_tests = 21
exec_file = './lab3'
path_to_tests = 'Tests/tests/test_'
path_to_answers = 'Tests/answers/answers_'
path_to_correct_answers = 'Tests/correct_answers/answers_'
exp = '.txt'

incorrect_ans = []

for i in range(number_of_tests):
    num = i + 1
    os.system(
        f'{exec_file} {path_to_tests}{num}{exp} > {path_to_answers}{num}{exp}')

    with open(f'{path_to_correct_answers}{num}{exp}') as corr_ans, \
            open(f'{path_to_answers}{num}{exp}') as ans, \
            open(f'{path_to_tests}{num}{exp}') as tests:
        ans_1 = corr_ans.readline().rstrip()
        ans_2 = ans.readline().rstrip()
        str_test = tests.readline()

    print(f'test_{num}:\n  string: {str_test}\n  correct answer: {ans_1}\n  program answer: {ans_2}\n  result: ', end='')
    if ans_1 == ans_2:
        print(f'correct')
    else:
        incorrect_ans.append(num)
        print(f'incorrect')

if len(incorrect_ans):
    print("\nIncorrect tests:", ", ".join(map(str, incorrect_ans)))
else:
    print("\nAll is OK")
