all: graph.exe graph2.exe

graph.exe: dlist.o graph.c
	gcc graph.c dlist.o -o graph.exe

graph2.exe: dlist.o graph2.c
	gcc graph2.c dlist.o -o graph2.exe

dlist.o: dlist.h dlist.c
	gcc -c dlist.c -o dlist.o

clean:
	del *.exe *.o