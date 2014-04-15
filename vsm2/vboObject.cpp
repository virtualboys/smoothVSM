

#include "vboObject.h"

vboObject::vboObject(float* vertexData, int numVertices)
{
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, vertexData, GL_STATIC_DRAW);
    
    this->numVertices = numVertices;
    numNormals = 0;
    normalVBO = -1;
    
    position = vec3(0,0,0);
    rotation = vec3(0,0,0);
    scale = 1;
}

vboObject::vboObject(std::vector<vec3> vertexData, std::vector<vec3> normalData)
{
    numVertices = vertexData.size();
    glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vec3), &vertexData[0], GL_STATIC_DRAW);
    
    numNormals = normalData.size();
    glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, numNormals * sizeof(vec3), &normalData[0], GL_STATIC_DRAW);
    
    position = vec3(0,0,0);
    rotation = vec3(0,0,0);
    scale = 1;
}

void
vboObject::setWorldMatrix()
{
    mat4 world = getWorldMatrix();
    glMultMatrixf(&world[0][0]);
}

mat4
vboObject::getWorldMatrix()
{
    mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, position);
    world = glm::rotate(world, rotation.x, vec3(1,0,0));
    world = glm::rotate(world, rotation.y, vec3(0,1,0));
    world = glm::rotate(world, rotation.z, vec3(0,0,1));
    world = glm::scale(world, vec3(scale, scale, scale));
    
    return world;
}

void
vboObject::draw(renderer* rend)
{
    
    rend->setShadingConstants(ka,kd);
    
    glPushMatrix();
    setWorldMatrix();
    
    rend->drawVBO(vertexVBO, numVertices, normalVBO);
    
    glPopMatrix();
}

