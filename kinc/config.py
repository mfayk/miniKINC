#####################################################################
#
# This file is licensed under the University of Illinois/NCSA Open 
# Source License. See LICENSE.TXT for details.
#
#####################################################################

#####################################################################
#
# Name: config.py
#
# Description: Default configuration file that is read by flipit-cc
#		flipit-cc will look in the cwd when compiling for this 
#		file, and if not found it will use the one in the 
#		SDCProp repo.
#
#####################################################################

############ LLVM BUILD TYPE ################
BUILD_TYPE = "Release+Asserts"
#BUILD_TYPE = "Debug+Asserts"

############### Injector Parameters ##################
#
#    config - config file used by the compiler pass
#    funcList - list of functions that are faulty
#    prob - probability that instuction is faulty
#    byte - which byte is faulty (0-7) -1 random
#    singleInj - one injection per active rank (0 or 1)
#    ptr - add code to inject into pointers (0 or 1)
#    arith - add code to inject into mathematics (0 or 1)
#    ctrl - add code to inject into control (0 or 1)
#
#####################################################
config = "KINC.config"
funcList = "\"\""
#prob = 0
prob = 1e-8
byte = -1
bit = -1
singleInj = 1
ptr = 1
arith = 1
ctrl = 1
stateFile = "KINC"

############# Library Parameters #####################
#
#    FLIPIT_PATH - Path to FlipIt repo
#    LLVM_BULID_PATH - Path to LLVM build directory
#    SHOW - libraries and path wraped by mpicc 
#
#####################################################

import os
FLIPIT_PATH = os.environ['FLIPIT_PATH'] 
LLVM_BUILD_PATH = os.environ['LLVM_BUILD_PATH'] 
#SHOW = " -I/opt/cray/mpt/7.3.0/gni/mpich-gnu/4.9/include -I/usr/local/include -L/usr/local/lib -lmpich -lopa -lmpl -lrt -lpthread "
SHOW = "  -I/usr/local/include -I//hpc/hpc/software/rpm/BUILD/mpich2-1.4.1p1/src/include -L/usr/local/lib -lmpich -lopa -lmpl -lrt -lpthread -L/hpc/hpc/software/rpm/BUILD/mpich2-1.4.1p1/lib"
#Palmetto 2017#SHOW = "  -I/usr/local/include -I//hpc/hpc/software/rpm/BUILD/mpich2-1.4.1p1/src/include -L/usr/local/lib -lmpich -lopa -lmpl -lrt -lpthread -L /usr/local/hpc/software/rpm/BUILDROOT/mpich2-1.4-2cu-1.x86_64/opt/mpich2/1.4/lib"
#t460s#SHOW = " -I/usr/lib/openmpi/include -I/usr/lib/openmpi/include/openmpi -lpthread -L/usr//lib -L/usr/lib/openmpi/lib -lmpi -ldl -lhwloc "
CPP_LIB = " -ldl -L/usr/lib/ -lm -lstdc++ "

########### Files to NOT inject inside ###############
notInject = ["main.cpp", "checkpoint", "restart"] 

############ Default Compiler ########################
#cc = "mpicxx"
cc = "gcc"

############ Verbose compiler output ################
verbose = True 

histogram = False
