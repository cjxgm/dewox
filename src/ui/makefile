
CC = gcc
CFLAGS = -Wall -s -O2
LIBS = -lglut

all: dewox
clean:
	rm -f *.o
	rm -f dewox
rebuild: clean all
debug: all
	./dewox

dewox: main.o backend.o ../util/list.o	\
		ui.o widget/button.o widget/label.o widget/font.o
	gcc $(CFLAGS) -o $@ $^ $(LIBS)
