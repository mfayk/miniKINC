#####################################################################
#
# Example that shows how to use the "flip-cc" compiler script. 
# In addition, it shows how to turn the injector on/off.
#
#####################################################################

CC=gcc
CFLAGS = -Wall -Wextra -g -I$(FLIPIT_PATH)/include

FILIB= -L$(FLIPIT_PATH)/lib -lcorrupt
FIPASS= $(FLIPIT_PATH)/lib/libFlipItPass.so
LFLAGS = $(FILIB)

test:	final.o ecc.o util.o main.o
	$(CC) -pg -g -o test final.o ecc.o util.o main.o $(FILIB)

work.o: work.c
	$(LLVM_BUILD_PATH)/bin/clang -fPIC $(CFLAGS) -emit-llvm work.c -c -o work.bc 
	$(LLVM_BUILD_PATH)/bin/llvm-link $(FLIPIT_PATH)/include/FlipIt/corrupt/corrupt.bc work.bc  -o crpt_work.bc
	$(LLVM_BUILD_PATH)/bin/opt -load $(FIPASS) -FlipIt -srcFile "work.c" -singleInj 1 -prob 0.95 -byte -1 -arith 1 -ctrl 0 -ptr 0 -funcList "" crpt_work.bc -o final.bc
	$(LLVM_BUILD_PATH)/bin/clang -fPIC -g -c final.bc -o final.o

ecc.o:	../sdecc/src/ecc.c ../sdecc/src/ecc.h
	$(CC) -c ../sdecc/src/ecc.c

util.o:	util.c util.h
	$(CC) -c util.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c


clean:
	rm -f *.bc
	rm -f main.o ecc.o util.o 
	rm -f *.LLVM.bin
	rm -f *.LLVM.txt
	rm -f *.gch
	rm -f *.pyc
	rm -f test
