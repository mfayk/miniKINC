#!/bin/bash
#####################################################################
#
# Simple example that corrupts 2+2. Here we use the long way of 
# compiling.
#
#####################################################################

# compile work.c
$LLVM_BUILD_PATH/bin/clang  -g -emit-llvm work.c  -c -o work.bc 
$LLVM_BUILD_PATH/bin/llvm-link $FLIPIT_PATH/include/FlipIt/corrupt/corrupt.bc work.bc  -o crpt_work.bc
$LLVM_BUILD_PATH/bin/opt -load $FLIPIT_PATH/lib/libFlipItPass.so -FlipIt -srcFile "work.c" -singleInj 1 -prob 0.95 -byte -1 -bit 0 -arith 1 -ctrl 0 -ptr 0 -funcList "" crpt_work.bc  -o final.bc
$LLVM_BUILD_PATH/bin/clang  -fPIC -g -c final.bc -o final.o  

# display the compiler log file for work.LLVM.txt
$FLIPIT_PATH/scripts/binary2ascii.py work.c.LLVM.bin -o work.c.LLVM.txt
cat work.c.LLVM.txt

# build the executable
gcc -c ../sdecc/src/ecc.c ../sdecc/src/ecc.h 
gcc -c util.c util.h
gcc -I$FLIPIT_PATH/include -o main.o -c main.c
gcc -o test final.o ecc.o util.o main.o -L$FLIPIT_PATH/lib/ -lcorrupt
./test
