

#ifndef renderHelper_h
#define renderHelper_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>

#include "glm/glm.hpp"

using namespace glm;

class renderer
{
public:
    
    int windowW;
    int windowH;
    GLuint toScreenShad;
    GLuint storeDepthShad;
    GLuint blurShad;
    
    renderer(int w, int h, GLuint toScreenShad, GLuint storeDepthShad, GLuint blurShad);
    
	void storeDepthBegin();
	void renderToScreenBegin(vec3 lPos);
    
    void drawVBO(GLuint vbo, int size);
    void drawVBO(GLuint vbo, int size, GLuint normalVBO);
    void drawIndexedVBO(GLuint vBuffer, GLuint iBuffer, int nIndices);
    
    void setShadingConstants(float ka, float kd);
    void setWorldMatrix(float tX, float tY, float tZ, float scale, float rY);
    void setWorldMatrix(mat4 world);
    
    void blurShadowBuffer();
    
private:
    
    GLuint shadowBuffer;
    GLuint shadowTexture;
    
    GLuint shadowTexULoc;
    GLuint kdULoc;
    GLuint kaULoc;
    GLuint lPosULoc;
    
	void initFrameBuffers();
    void setTextureMatrix();
    
};

#endif
