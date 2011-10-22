
CC = gcc
CFLAGS = -Wall -s -O2
LIBS = -lglut

OBJ_UI_WIDGET = ui/widget/button.o ui/widget/label.o ui/widget/font.o
OBJ_UI = ui/ui.o $(OBJ_UI_WIDGET)

OBJ_UTIL = util/list.o

OBJ_DEWOX = main.o backend.o

OBJS = $(OBJ_DEWOX) $(OBJ_UTIL) $(OBJ_UI)

all: dewox
clean:
	rm -f *.o
	rm -f dewox
	make clean -C ui
	make clean -C util
rebuild: clean all
debug: all
	./dewox

dewox: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

