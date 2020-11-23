#! /bin/bash

printf "\nLaunching the tests\n\n"
for n in {0..6}
do
    printf "Test$n:\n"
    ./lab4 < "./Tests/test$n.txt"
    printf "\n"
done
for n in {7..9}
do
	printf "Test$n:\n"
	printf "Error expected\nResult is\t"
	./lab4 < "./Tests/wrong_test$n.txt"
	printf "\n"
done
