.Phony : all clean

all : test

test : test.c buddy_system.c
		gcc -g -Wall -o $@ $^

clean :
		rm -f test test.exe
