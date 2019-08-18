PROGRAM = mat_lav
CC      = gcc
CFLAGS  = -g -ansi -std=c11 -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): mat_lav.o image.o 
	$(CC) $(LDFLAGS) -o $(PROGRAM) mat_lav.o image.o $(LDLIBS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
