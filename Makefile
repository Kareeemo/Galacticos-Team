# Each teammate can override this locally to point to their own SFML install.
SFML_PATH ?= C:\SFML-3.0.0

CXX := g++
CXXFLAGS := -I"$(SFML_PATH)\include" -DSFML_STATIC
LDFLAGS := -L"$(SFML_PATH)\lib"
LDLIBS := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

SOURCES := Main.cpp Player.cpp Level.cpp Physics.cpp Render.cpp Ui.cpp
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := Main.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.exe *.o 2>nul
