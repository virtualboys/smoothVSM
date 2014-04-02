
#ifndef _loadShader
#define _loadShader

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glxext.h>
#endif


GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
