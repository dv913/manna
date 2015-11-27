#!/bin/bash
gcc manna_scan_clean.c -o scan_test_ran.x -lm
gcc manna_stack_clean.c -o stack_test_ran.x -lm
rm scan_arr.dat stack_arr.dat
echo "scan timing"
time ./scan_test_ran.x >> scan_arr.dat
echo "stack timing"
time ./stack_test_ran.x >> stack_arr.dat

vimdiff scan_arr.dat stack_arr.dat

