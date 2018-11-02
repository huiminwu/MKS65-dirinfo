all: dir.o
	gcc -o Dir dir.o

dir.o: dir.c
	gcc -c dir.c

run:
	./Dir
