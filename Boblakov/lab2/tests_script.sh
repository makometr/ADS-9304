#! /bin/bash

printf "\nRunning tests...\n\n"
for n in {1..10}
do
    ./lab2 < "./Tests/tests/test$n.txt" > "./Tests/out/out$n.txt"
    printf "Test$n: "
    cat "./Tests/tests/test$n.txt" | tr -d '\n'
    if cmp "./Tests/out/out$n.txt" "./Tests/true_results/true_out$n.txt" > /dev/null; then
	    printf " - Passed\n"
    else
     	    printf " - Failed\n"
    fi
    printf "Desired result:\n"
    cat "./Tests/true_results/true_out$n.txt"
    printf "Actual result:\n"
    cat "./Tests/out/out$n.txt"
    printf "==============\n"  
done
rm ./Tests/out/out*
