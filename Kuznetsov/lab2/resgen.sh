#!/bin/sh
for i in 1 2 3 4 5 6 7 8 9 10
do
./main.exe < Tests/test$i.txt > Tests/testres$i.txt
done
