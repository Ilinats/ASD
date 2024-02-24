all: graph.exe

graph.exe: dlist.o graph.c
	gcc graph.c dlist.o -o graph.exe

dlist.o: dlist.h dlist.c
	gcc -c dlist.c -o dlist.o

clean:
	del *.exe *.o