#!/bin/sh
export PYTHONPATH=../Output/lib
for file in *.py
do
    python $file
done
