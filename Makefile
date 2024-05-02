CC = g++	# use g++ for compiling c++ code
CFLAGS = -g -Wall -std=c++17		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.

all: test
SRCS = linkedlist.cpp htable.cpp test.cpp order.cpp Main.cpp
DEPS = $(SRCS:.cpp=.d)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

test: test.o linkedlist.o htable.o order.o
	$(CC) test.o linkedlist.o htable.o order.o -o test

test1: test1.o linkedlist.o
	$(CC) test1.o linkedlist.o -o test1

clean:
	rm *.o test
