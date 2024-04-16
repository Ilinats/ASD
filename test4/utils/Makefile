all: main.exe

main.exe: dlist.o graph_matrix.o main_2.c
	gcc main_2.c dlist.o graph_matrix.o -o main.exe

dlist.o: dlist.h dlist.c
	gcc -c dlist.c -o dlist.o

graph_matrix.o: graph_matrix.h graph_matrix.c
	gcc -c graph_matrix.c -o graph_matrix.o

clean:
	del *.exe *.o