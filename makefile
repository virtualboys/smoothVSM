
smooth: smooth.o gltb.o glm.o loadShader.o
	g++ -std=c++0x -w -o smooth smooth.o gltb.o glm.o loadShader.o -framework OpenGL -framework GLUT
smooth.o: smooth.c gltb.h glm.h dirent32.h loadShader.h
	g++ -w -c -o smooth.o smooth.c
gltb.o: gltb.c gltb.h
	g++ -w -c -o gltb.o gltb.c
glm.o: glm.c glm.h
	g++ -w -c -o glm.o glm.c
loadShader.o: loadShader.cpp loadShader.h
	gcc -w -c -o loadShader.o loadShader.cpp
clean:
	rm smooth smooth.o gltb.o glm.o loadShader.o