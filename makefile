CC = gcc
CFLAGS = -g3 -std=c99 -pedantic -Wall

maze_solver: maze_solver.o cs50.o
	${CC} ${CFLAGS} -o maze_solver $^

maze_solver.o: maze_solver.c
	${CC} ${CFLAGS} -c maze_solver.c

cs50.o: cs50.c cs50.h
	${CC} ${CFLAGS} -c cs50.c
