#! /bin/bash

printf "\nLaunching the tests\n\n"
for n in {1..1}
do
    printf "Test$n:\n"
    ./a.out < Test/test$n.txt
    printf "\n"
    cat "./Test/test$n.txt" | tr -d '\n'
    if cmp "./res_enc_h.txt" "./Test/true_out$n.txt" > /dev/null; then
            printf "\n*** - Passed\n"
    else
            printf "\n*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Test/true_out$n.txt"
    printf "Actual result:\n"
    cat "./res_enc_h.txt"
    printf "\n==============\n"

done
for n in {2..2}
do
    printf "Test$n:\n"
    ./a.out < Test/test$n.txt
    printf "\n"
    cat "./Test/test$n.txt" | tr -d '\n'
    if cmp "./res_enc_f.txt" "./Test/true_out$n.txt" > /dev/null; then
            printf "\n*** - Passed\n"
    else
            printf "\n*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Test/true_out$n.txt"
    printf "Actual result:\n"
    cat "./res_enc_f.txt"
    printf "\n==============\n"

done
for n in {3..3}
do
    printf "Test$n:\n"
    ./a.out < Test/test$n.txt
    printf "\n"
    cat "./Test/test$n.txt" | tr -d '\n'
    if cmp "./res_dec_h.txt" "./Test/true_out$n.txt" > /dev/null; then
            printf "\n*** - Passed\n"
    else
            printf "\n*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Test/true_out$n.txt"
    printf "Actual result:\n"
    cat "./res_dec_h.txt"
    printf "\n==============\n"

done
for n in {4..4}
do
    printf "Test$n:\n"
    ./a.out < Test/test$n.txt
    printf "\n"
    cat "./Test/test$n.txt" | tr -d '\n'
    if cmp "./res_dec_f.txt" "./Test/true_out$n.txt" > /dev/null; then
            printf "\n*** - Passed\n"
    else
            printf "\n*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Test/true_out$n.txt"
    printf "Actual result:\n"
    cat "./res_dec_f.txt"
    printf "\n==============\n"

done
for n in {5..5}
do
    printf "Test$n:\n"
    ./a.out <Test/test$n.txt > out$n.txt 
    printf "qw\n" 
    if cmp "./out$n.txt" "./Test/true_out$n.txt" > /dev/null; then
            printf "*** - Passed\n"
    else
            printf "*** - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Test/true_out$n.txt"
    printf "Actual result:\n"
    cat "./out$n.txt"
    printf "\n==============\n"

done

#rm ./out*.txt
#rm ./pairs*.txt
