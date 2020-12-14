#!/bin/bash

mkdir "./Tests/Output"

printf "Running tests...\n"

for i in {1..8}
do
    ./lab3 < "./Tests/Tests/Test$i.txt" > "./Tests/Output/Output$i.txt"
    printf "Test$i: "
    cat "./Tests/Tests/Test$i.txt" | tr -d '\n'
    if cmp "./Tests/Output/Output$i.txt" "./Tests/True_result/True_result$i.txt";
    then
        printf " - Passed\n\n"
    else
        printf " - Failed\n\n"
    fi  
    printf "Result:\n"
    cat "./Tests/Output/Output$i.txt"
    printf "Expected result:\n"
    cat "./Tests/True_result/True_result$i.txt"
    echo
    echo
done

rm -rf "./Tests/Output"
