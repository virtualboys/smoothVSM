
#ifndef _loadShader
#define _loadShader

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>


GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif