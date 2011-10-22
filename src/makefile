
CC = g++
CFLAGS = -Wall -s -O2
LIBS = -lglut

OBJ_UI_WIDGET = UI/Widget/Button.o UI/Widget/Label.o UI/Widget/Font.o
OBJ_UI = UI/UI.o UI/RGB.o $(OBJ_UI_WIDGET)

OBJ_UTIL = Util/List.o

OBJ_DEWOX = main.o Backend.o

OBJS = $(OBJ_DEWOX) $(OBJ_UTIL) $(OBJ_UI)

all: dewox
clean:
	rm -f *.o
	rm -f dewox
	make clean -C UI
	make clean -C Util
rebuild: clean all
debug: all
	./dewox

dewox: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

