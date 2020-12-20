#! /bin/bash

printf "\nLaunching the tests\n\n"
for n in {1..4}
do
    printf "Test$n:\n"
    ./lab5 -e -f Tests/test$n.txt -o out$n.txt 
    cat "./Tests/test$n.txt" #| tr -d '\n'
    if cmp "./out$n.txt" "./Tests/true_out$n.txt" > /dev/null; then
            printf "*** - Passed\n"
    else
            printf "*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Tests/true_out$n.txt"
    printf "Actual result:\n"
    cat "./out$n.txt"
    printf "\n==============\n"

done
for n in {5..8}
do
    printf "Test$n:\n"
    ./lab5 -d Tests/pairs$n.txt -f Tests/test$n.txt -o out$n.txt 
    cat "./Tests/test$n.txt" #| tr -d '\n'
    if cmp "./out$n.txt" "./Tests/true_out$n.txt" > /dev/null; then
            printf "*** - Passed\n"
    else
            printf "*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Tests/true_out$n.txt"
    printf "Actual result:\n"
    cat "./out$n.txt"
    printf "\n==============\n"

done
for n in {9..9}
do
    printf "Test$n:\n"
    ./lab5 -e > out$n.txt 
    printf "./lab5 -e\n" 
    if cmp "./out$n.txt" "./Tests/true_out$n.txt" > /dev/null; then
            printf "*** - Passed\n"
    else
            printf "*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Tests/true_out$n.txt"
    printf "Actual result:\n"
    cat "./out$n.txt"
    printf "\n==============\n"

done
for n in {10..10}
do
    printf "Test$n:\n"
    ./lab5 abcqwezxc > out$n.txt 
    printf "./lab5 abcqwezxc\n" 
    if cmp "./out$n.txt" "./Tests/true_out$n.txt" > /dev/null; then
            printf "*** - Passed\n"
    else
            printf "*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Tests/true_out$n.txt"
    printf "Actual result:\n"
    cat "./out$n.txt"
    printf "\n==============\n"

done



rm ./out*.txt
#rm ./pairs*.txt
