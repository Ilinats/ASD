all: selection_sort.exe

selection_sort.exe: vector.o tests.c
	gcc selection_sort.c vector.o -o selection_sort.exe

vector.o: vector.h vector.c
	gcc -c vector.c -o vector.o

clean:
	del *.exe *.o