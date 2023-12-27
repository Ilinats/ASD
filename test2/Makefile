CC = gcc
CFLAGS = -Wall -Wextra -g
INC = -I.

all: a.exe

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c $(INC) -o stack.o

tree.o: tree.c tree.h stack.h
	$(CC) $(CFLAGS) -c tree.c $(INC) -o tree.o

main.o: main.c tree.h stack.h
	$(CC) $(CFLAGS) -c main.c $(INC) -o main.o

a.exe: main.o stack.o tree.o
	$(CC) $(CFLAGS) $^ -o a.exe