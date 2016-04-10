all: sample2D

sample2D: glfw.cpp glad.c
	g++ -o sample2D glfw.cpp glad.c -lGL -lglfw -ldl  -lftgl -lSOIL -I/usr/local/include -I/usr/local/include/freetype2 -L/usr/local/lib 

clean:
	rm sample2D sample3D
