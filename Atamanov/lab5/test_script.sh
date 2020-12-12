#!/bin/bash

mkdir "./Tests/Output"

echo "Running tests...\n"

for i in {1..14}
do
	while read line; do
		testarray[$i]="$line"
	done < ./Tests/Tests/Test$i/Test$i.txt
done

for i in {1..14}
do
	if [[ "${testarray[$i]}" == *"-o"* ]];
	then
		if [[ "${testarray[$i]}" == *"-f"* ]];
		then
			./lab5 ${testarray[$i]}
			mv "./Output.txt" "./Tests/Output/Output$i.txt"
		else
			./lab5 ${testarray[$i]} < "./Tests/Tests/Test$i/Enter.txt"
			mv "./Output.txt" "./Tests/Output/Output$i.txt"
		fi
	else
		if [[ "${testarray[$i]}" == *"-f"* ]];
		then
			./lab5 ${testarray[$i]} > "./Tests/Output/Output$i.txt"
		else
			./lab5 ${testarray[$i]} < "./Tests/Tests/Test$i/Enter.txt" > "./Tests/Output/Output$i.txt"
		fi
	fi
	printf "Test$i: "
	cat "./Tests/Tests/Test$i/Test$i.txt"
	cat "./Tests/Tests/Test$i/Enter.txt" | tr -d '\n'
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
