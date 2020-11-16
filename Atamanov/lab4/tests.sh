#!/bin/bash

echo "Running tests..."
for n in {1..9}
do
	echo "test$n:"
	./lab4 < "./Tests/test$n.txt"
	echo ""
done
