
CXX = g++
CXXFLAGS = -Wall -s -O2
LIBS = -lglut

OBJ_UI_WIDGET = UI/Widget/Button.o \
				UI/Widget/Label.o \
				UI/Widget/Font.o \
				UI/Widget/Frame.o \
				UI/Widget/VSplit.o \
				UI/Widget/HSplit.o \
				UI/Widget/Menubar.o
OBJ_UI = UI/UI.o UI/RGB.o \
		 UI/ColorManager.o \
		 UI/EventManager.o \
		 $(OBJ_UI_WIDGET)

OBJ_UTIL = Util/List.o

OBJ_DEWOX = Dewox/Dewox.o \
			Dewox/Backend.o \
			Dewox/App.o \
			$(OBJ_UTIL) $(OBJ_UI)

all: dewox
clean:
	rm -f *.o
	rm -f dewox
	rm -f dewox.log
	make clean -C UI
	make clean -C Util
	make clean -C Dewox
rebuild: clean all
debug: all
	./dewox

dewox: $(OBJ_DEWOX)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

