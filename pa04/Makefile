CC	=	gcc
FLAGS	=	-std=c99 -D_SVID_SOURCE

all: greedy04.c minPQ.c adjWgtVec.c loadWgtGraph.c
	$(CC) -c $(FLAGS) greedy04.c minPQ.c adjWgtVec.c loadWgtGraph.c

greedy04: greedy04.o minPQ.o adjWgtVec.o loadWgtGraph.o
	$(CC) $(FLAGS) -o greedy04 greedy04.c minPQ.c adjWgtVec.c loadWgtGraph.c

clean:
	rm -f greedy04 *o out_file.txt
