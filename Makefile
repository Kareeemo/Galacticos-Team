all: compile link

compile:
	g++ Main.cpp -o Main -I"C:\SFML-3.0.0\include" -L"C:\SFML-3.0.0\lib" -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32
 -lfreetype -lwinmm -lgdi32 -mwindows

link:
	g++ Main.cpp -o Main -I"C:\Users\karim\Documents\libraries\SFML-3.0.0\include" -L"C:\Users\karim\Documents\libraries\SFML-3.0.0\lib" -DSFML_STATIC -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

clean:
	-del /Q Main.exe *.o