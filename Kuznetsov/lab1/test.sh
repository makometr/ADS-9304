#!/bin/sh
./compile.sh
for i in 1 2 3 4 5 6 7 8 9 10
do
./main.exe < Tests/test$i.txt > Tests/result.txt && ./unitTests.exe < Tests/result.txt
done
rm Tests/result.txt