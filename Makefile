all: marcoyolo

marcoyolo: marcoyolo.c marcoyolo.h
	gcc --std=c99 -ansi -pedantic -Wall -g -o marcoyolo marcoyolo.c

run: marcoyolo
	./marcoyolo

clean:
	rm -f marcoyolo
