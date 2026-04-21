# Each teammate should change this to their local SFML path.
SFML_PATH = C:\SFML-3.0.0

CXX = g++
CXXFLAGS = -I$(SFML_PATH)\include
LDFLAGS = -L$(SFML_PATH)\lib -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

OBJECTS = Main.o Player.o Level.o Physics.o Render.o Ui.o
TARGET = Main.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) -c Main.cpp -o Main.o

Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -c Player.cpp -o Player.o

Level.o: Level.cpp
	$(CXX) $(CXXFLAGS) -c Level.cpp -o Level.o

Physics.o: Physics.cpp
	$(CXX) $(CXXFLAGS) -c Physics.cpp -o Physics.o

Render.o: Render.cpp
	$(CXX) $(CXXFLAGS) -c Render.cpp -o Render.o

Ui.o: Ui.cpp
	$(CXX) $(CXXFLAGS) -c Ui.cpp -o Ui.o

clean:
	del /Q Main.exe *.o
