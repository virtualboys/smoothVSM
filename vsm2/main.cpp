#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#endif

#include <vector>
#include <iostream>

#include "Camera.h"
#include "f3.h"
#include "renderer.h"
#include "loadShader.h"
#include "vboObject.h"
#include "objloader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#define WINDOW_W 600
#define WINDOW_H 600

#define BLUR_RES .5
#define SHADOW_RES .5

#define PI 3.14159

using namespace glm;

renderer* rend;
Camera* playerCam;
Camera* lightCam;

vboObject* plane;
vboObject* suzanne;

void
init()
{
    glEnable(GL_DEPTH_TEST);
    
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);
    
	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
    
    //GLuint toScreenShad = loadShaders("shaders/VertexShader.c", "shaders/FragmentShader.c");
    GLuint storeDepthShad= loadShaders("shaders/StoreDepthVertexShader.c", "shaders/StoreDepthFragmentShader.c");
    GLuint toScreenShad = loadShaders("shaders/ShadowMapping_SimpleVersion.vertexshader", "shaders/ShadowMapping_SimpleVersion.fragmentshader");
    //GLuint storeDepthShad= loadShaders("shaders/DepthRRT.vertexshader", "shaders/DepthRRT.fragmentshader");
    GLuint blurShad = loadShaders("shaders/vShader.c", "shaders/fShader.c");
    
    playerCam = new Camera(0,0,-8, 0,0,0);
    lightCam = new Camera(0,0,-3, 0,0,0);
    
    GLint lPosULoc = glGetUniformLocation(toScreenShad, "lPos");
    glUniform4f(lPosULoc, lightCam->pos->x, lightCam->pos->y, lightCam->pos->z, 1);
    
    rend = new renderer(WINDOW_W, WINDOW_H, toScreenShad, storeDepthShad, blurShad);
    
    
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<glm::vec2> uvs;
    bool res = loadOBJ("models/suzanne.obj", vertices, uvs, normals);

    
    suzanne = new vboObject(vertices, normals);
    suzanne->position = vec3(0,0,-2);
    suzanne->rotation = vec3(0,180,0);
    suzanne->scale = .3f;
    
    GLfloat planeVBData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };
    
    plane = new vboObject(&planeVBData[0], 6);

}

void
display()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    rend->storeDepthBegin();
    lightCam->setMatrices();
    
    plane->draw(rend);
    suzanne->draw(rend);
    
    rend->renderToScreenBegin(vec3(lightCam->pos->x,lightCam->pos->y,lightCam->pos->z));
    playerCam->setMatrices();
    
    rend->setWorldMatrix(mat4(1.0f));
    plane->draw(rend);
    
    rend->setWorldMatrix(suzanne->getWorldMatrix());
    suzanne->draw(rend);
    
    glutSwapBuffers();
    
    glutPostRedisplay();
}

void
keyboard(unsigned char key, int x, int y)
{
    f3* right = playerCam->getRight();
    f3* forward = playerCam->getDirection();
    
    switch(key)
    {
            
        case 'a':
            right->multscalar(.1f);
            playerCam->pos->sub(right);
            break;
        case 'd':
            right->multscalar(.1f);
            playerCam->pos->add(right);
            break;
        case 'w':
            forward->multscalar(.1f);
            playerCam->pos->add(forward);
            break;
        case 's':
            forward->multscalar(.1f);
            playerCam->pos->sub(forward);
            break;
        case 'q':
            playerCam->rot->x+=.1f;
            break;
        case 'e':
            playerCam->rot->x-=.1f;
            break;
            
        default:
            break;
    }
    
    glutPostRedisplay();
}

int
main(int argc, char *argv[])
{
    
	glutInit(&argc, argv);
    
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("test");
    
	glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
	glClearColor(.50, .50, .50, 1.0);
    
    init();
	glutMainLoop();
    
    return 0;
}
