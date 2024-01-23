all: main.exe

main.exe: quadTree.o figure.o main.c
	gcc main.c quadTree.o figure.o -o main.exe

quadTree.o: quadTree.h quadTree.c
	gcc -c quadTree.c -o quadTree.o

figure.o: figure.h figure.c
	gcc -c figure.c -o figure.o

clean:
	del *.exe *.o