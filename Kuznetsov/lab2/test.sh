#!/bin/sh
./compile.sh
./resgen.sh
cp Source/tests.py ./tests.py
python Source/tests.py

rm main.exe tests.py
for i in 1 2 3 4 5 6 7 8 9 10
do
rm Tests/testres$i.txt
done

