all: input.o
	gcc -o Dir input.o

dir.o: dir.c
	gcc -c dir.c

input.o: dir.c input.c
	gcc -c dir.c input.c

run:
	./Dir
