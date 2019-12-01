#####################################################################
#
# Example that shows how to use the "flip-cc" compiler script. 
# In addition, it shows how to turn the injector on/off.
#
#####################################################################

CC=gcc
CFLAGS = -g -I$(FLIPIT_PATH)/include

FILIB= -L$(FLIPIT_PATH)/lib -lcorrupt
FIPASS= $(FLIPIT_PATH)/lib/libFlipItPass.so
LFLAGS = $(FILIB)
OBJ = final.o ecc.o util.o main.o 

test:	$(OBJ)
	$(CC) -o test $(OBJ) $(FILIB)

work.o: work.c
	$(LLVM_BUILD_PATH)/bin/clang -fPIC $(CFLAGS) -emit-llvm work.c -c -o work.bc 
	$(LLVM_BUILD_PATH)/bin/llvm-link $(FLIPIT_PATH)/include/FlipIt/corrupt/corrupt.bc work.bc  -o crpt_work.bc
	$(LLVM_BUILD_PATH)/bin/opt -load $(FIPASS) -FlipIt -srcFile "work.c" -singleInj 1 -prob 0.95 -byte -1 -arith 1 -ctrl 0 -ptr 0 -funcList "" crpt_work.bc -o final.bc
	$(LLVM_BUILD_PATH)/bin/clang  -fPIC -g -c final.bc -o final.o

ecc.o:	../sdecc/src/ecc.c ../sdecc/src/ecc.h
	$(CC) -c ../sdecc/src/ecc.c

util.o:	util.c util.h
	$(CC) -c util.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

#short: _work.o _main.o
#	$(CC) -o short _work.o _main.o $(LFLAGS)

#_work.o: work.c
#	$(FLIPIT_PATH)/scripts/flipit-cc $(CFLAGS) -fPIC -o _work.o -c work.c

#_main.o: main.c
#	$(FLIPIT_PATH)/scripts/flipit-cc $(CFLAGS) -o _main.o -c main.c

clean:
	rm -f *.bc
	rm -f main.o ecc.o util.o 
	rm -f *.LLVM.bin
	rm -f *.gch
	rm -f *.pyc
	rm -f test
