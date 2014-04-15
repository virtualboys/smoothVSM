OBJDIR := build

main: main.o loadShader.o renderer.o f3.o Camera.o objloader.o vboObject.o
	g++ -w -o main main.o loadShader.o renderer.o f3.o Camera.o objloader.o vboObject.o -framework OpenGL -framework GLUT

main.o: main.cpp loadShader.h renderer.h Camera.h objloader.hpp vboObject.h
	g++ -w -c -o main.o main.cpp

loadShader.o: loadShader.cpp loadShader.h
	g++ -w -c -o loadShader.o loadShader.cpp

renderer.o: renderer.cpp renderer.h
	g++ -w -c -o renderer.o renderer.cpp

f3.o: f3.cpp f3.h
	g++ -w -c -o f3.o f3.cpp

Camera.o: Camera.h Camera.cpp f3.h
	g++ -w -c -o camera.o camera.cpp

objloader.o: objloader.cpp objloader.hpp
	g++ -w -c -o objloader.o objloader.cpp

vboObject.o: vboObject.cpp vboObject.h renderer.h
	g++ -w -c -o vboObject.o vboObject.cpp

clean:
	rm main main.o loadShader.o renderer.o f3.o Camera.o objloader.o vboObject.o
