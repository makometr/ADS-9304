#!/bin/bash
if [[ ! -e ./Tests/output.txt ]]
then
	touch ./Tests/output.txt
elif [[ -s ./Tests/output.txt ]]
then
	rm ./Tests/output.txt
	touch ./Tests/output.txt
fi

index=0
while read line; do
	testarray[$index]="$line"
	index=$(($index+1))
done < ./Tests/testfile.txt

index=0
while read line; do
	answerarray[$index]="$line"
	index=$(($index+1))
done < ./Tests/answer.txt

exec 1> ./Tests/output.txt
for((i=0;i < ${#testarray[*]};i++)); do
	./lab1 ${testarray[$i]}
done

index=0
while read line; do
	outputarray[$index]="$line"
	index=$(($index+1))
done < ./Tests/output.txt

rm ./Tests/output.txt
touch ./Tests/output.txt

exec 1> ./Tests/output.txt
for((i=0;i < ${#answerarray[*]};i++)); do
	if [[ ${outputarray[$i]} = ${answerarray[$i]} ]]
	then
		echo "${outputarray[$i]} Correct"
	else
		echo "${outputarray[$i]} Incorrect"
	fi
done
