all: main.exe

main.exe: tree.o main.c
	gcc main.c tree.o -o main.exe

tree.o: tree.h tree.c
	gcc -c tree.c -o tree.o

clean:
	del *.exe *.o