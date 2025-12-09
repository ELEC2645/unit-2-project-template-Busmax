# makefile for building the program. Each of these can be run from the command line like "make hello.out".
# "make clean" deletes the exectuable to build again 
# "make test" builds the main file and then runs the test script. This is what the autograder uses
# 
# Note to students: You dont need to fully understand this! 

main.out: main.c funcs.c funcs.h
	gcc main.c funcs.c -o main.out -lm

clean:
	-rm main.out libeng.so

test: clean main.out
	bash test.sh

libeng.so: funcs.c funcs.h
	gcc -shared -o libeng.so funcs.c -lm -fPIC 
