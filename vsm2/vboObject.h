
#ifndef ____vboObject__
#define ____vboObject__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#endif

#include <vector>

#include "renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define K_D .6
#define K_A .2

using namespace glm;

class vboObject
{
public:
    GLuint vertexVBO;
    int numVertices;
    GLuint normalVBO;
 	int numNormals;
    
    vec3 position;
    vec3 rotation;
    float scale;
    
    float kd = K_A;
    float ka = K_D;
    
    vboObject(float* vertexData, int size);
    vboObject(std::vector<vec3> vertexData, std::vector<vec3> normalData);
    
    void setWorldMatrix();
    mat4 getWorldMatrix();
    
    void draw(renderer* rend);
};

#endif /* defined(____vboObject__) */
