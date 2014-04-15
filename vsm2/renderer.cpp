

#include "renderer.h"


renderer::renderer(int w, int h, GLuint toScreenShad, GLuint storeDepthShad, GLuint blurShad)
{
    this->windowW = w;
    this->windowH = h;
    this->toScreenShad = toScreenShad;
    this->storeDepthShad = storeDepthShad;
    this->blurShad = blurShad;
    
    shadowTexULoc = glGetUniformLocation(toScreenShad, "shadowMap");
    kaULoc = glGetUniformLocation(toScreenShad, "ka");
    kdULoc = glGetUniformLocation(toScreenShad, "kd");
	lPosULoc = glGetUniformLocation(toScreenShad, "lPos");
    
    initFrameBuffers();
}

void
renderer::initFrameBuffers()
{
 
    shadowBuffer = 0;
    glGenFramebuffers(1, &shadowBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
    
    glGenTextures(1, &shadowTexture);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, shadowTexture);
    
    // Give an empty image to OpenGL ( the last "0" )
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowW, windowH, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, windowW, windowH, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    
    
    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, shadowTexture, 0);
    
    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
    /*
    glGenFramebuffers(1, &shadowBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
	glGenTextures(1, &shadowTexture);
	glBindTexture(GL_TEXTURE_2D, shadowTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, windowW, windowH, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTexture, 0);
    
	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "BAD" << endl;
    */
}

void
renderer::storeDepthBegin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
    glViewport(0,0,windowW,windowH);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(storeDepthShad);
}

void
renderer::renderToScreenBegin(vec3 lPos)
{
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,windowW,windowH);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(toScreenShad);
    glUniform4f(lPosULoc, lPos.x, lPos.y, lPos.z, 1);
    setTextureMatrix();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowTexture);
    glUniform1i(shadowTexULoc, 0);

}

void
renderer::drawIndexedVBO(GLuint vBuffer, GLuint iBuffer, int nIndices)
{
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    // Draw the triangles !
    glDrawElements(
                   GL_TRIANGLES,      // mode
                   nIndices,    // count
                   GL_UNSIGNED_INT,   // type
                   (void*)0           // element array buffer offset
                   );
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void
renderer::drawVBO(GLuint vbo, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glVertexPointer(3, GL_FLOAT, 0, 0);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void
renderer::drawVBO(GLuint vbo, int size, GLuint normalVBO)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glNormalPointer(GL_ARRAY_BUFFER, 0, 0);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void
renderer::blurShadowBuffer()
{/*
    //glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	
	// Bluring the shadow map  horinzontaly
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,blurFboId);
    glViewport(0,0,RENDER_WIDTH * SHADOW_MAP_COEF *BLUR_COEF ,RENDER_HEIGHT* SHADOW_MAP_COEF*BLUR_COEF);
    glUseProgramObjectARB(blurShader);
    glUniform2fARB(scaleUniform,1.0/ (RENDER_WIDTH * SHADOW_MAP_COEF * BLUR_COEF),0.0);		// Bluring horinzontaly
    glUniform1iARB(textureSourceUniform,0);
    glActiveTextureARB(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,colorTextureId);
    
    //Preparing to draw quad
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-RENDER_WIDTH/2,RENDER_WIDTH/2,-RENDER_HEIGHT/2,RENDER_HEIGHT/2,1,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //Drawing quad
    glTranslated(0,0,-5);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);glVertex3f(-RENDER_WIDTH/2,-RENDER_HEIGHT/2,0);
    glTexCoord2d(1,0);glVertex3f(RENDER_WIDTH/2,-RENDER_HEIGHT/2,0);
    glTexCoord2d(1,1);glVertex3f(RENDER_WIDTH/2,RENDER_HEIGHT/2,0);
    glTexCoord2d(0,1);glVertex3f(-RENDER_WIDTH/2,RENDER_HEIGHT/2,0);
    glEnd();
    //glGenerateMipmapEXT(GL_TEXTURE_2D);
    
    
    // Bluring vertically
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId);
    glViewport(0,0,RENDER_WIDTH * SHADOW_MAP_COEF ,RENDER_HEIGHT* SHADOW_MAP_COEF);
    glUniform2fARB(scaleUniform,0.0, 1.0/ (RENDER_HEIGHT * SHADOW_MAP_COEF ) );
    glBindTexture(GL_TEXTURE_2D,blurFboIdColorTextureId);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);glVertex3f(-RENDER_WIDTH/2,-RENDER_HEIGHT/2,0);
    glTexCoord2d(1,0);glVertex3f(RENDER_WIDTH/2,-RENDER_HEIGHT/2,0);
    glTexCoord2d(1,1);glVertex3f(RENDER_WIDTH/2,RENDER_HEIGHT/2,0);
    glTexCoord2d(0,1);glVertex3f(-RENDER_WIDTH/2,RENDER_HEIGHT/2,0);
    glEnd();*/
}

void
renderer::setShadingConstants(float ka, float kd)
{
    glUniform1f(kaULoc, ka);
    glUniform1f(kdULoc, kd);
}

void
renderer::setWorldMatrix(float tX, float tY, float tZ, float scale, float rY)
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(tX, tY, tZ);
    glScalef(scale, scale, scale);
    glRotatef(rY,0,1,0);
    
    float* worldMat = new float[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, worldMat);
    
    GLint worldMatLoc = glGetUniformLocation(toScreenShad, "world");
    glUniformMatrix4fv(worldMatLoc, 1, GL_FALSE, worldMat);
    
    glPopMatrix();
}

void
renderer::setWorldMatrix(mat4 world)
{
    GLint worldMatLoc = glGetUniformLocation(toScreenShad, "world");
    glUniformMatrix4fv(worldMatLoc, 1, GL_FALSE, &world[0][0]);
}

void
renderer::setTextureMatrix()
{
	static double modelView[16];
	static double projection[16];
	
	// This is matrix transform every coordinate x,y,z
	// x = x* 0.5 + 0.5
	// y = y* 0.5 + 0.5
	// z = z* 0.5 + 0.5
	// Moving from unit cube [-1,1] to [0,1]
	const GLdouble bias[16] = {
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0};
	
	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	
	glLoadIdentity();
	glLoadMatrixd(bias);
	
	// concatating all matrice into one.
	glMultMatrixd (projection);
	glMultMatrixd (modelView);
	
	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}





