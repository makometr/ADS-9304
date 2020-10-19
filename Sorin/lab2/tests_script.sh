#! /bin/bash

printf "\nRunning tests...\n\n"
for n in {1..6}
do
    ./lab2 < "./tests/test_in/in$n.txt" > "./tests/test_out/out$n.txt"
    printf "Test$n: "
    cat "./Tests/test_in/in$n.txt" | tr -d '\n'
    if cmp "./tests/test_out/out$n.txt" "./tests/currect_results/res$n.txt" > /dev/null; then
	    printf " - test passed\n"
    else
     	    printf " - test failed\n"
    fi
    printf "Expected result:\n"
    cat "./tests/currect_results/res$n.txt"
    printf "Actual result:\n"
    cat "./tests/test_out/out$n.txt"
    printf "==============\n"  
done
rm ./tests/test_out/out*