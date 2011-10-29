
CC = gcc
CFLAGS = -Wall -s -Ofast
LIBS = -lglut -lm


OBJ_MAIN = main.o video.o pager.o widget.o pagefile.o font.o
OBJS = $(OBJ_MAIN)


all: dewox
clean:
	rm -f *.o
	rm -f dewox
rebuild: clean all
debug: all
	./dewox

dewox: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

