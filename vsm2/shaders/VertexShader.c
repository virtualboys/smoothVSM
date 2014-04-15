// Used for shadow lookup

varying vec4 ShadowCoord;
varying vec3 norm;
varying vec3 pos;

void main()
{


    ShadowCoord = gl_TextureMatrix[7] * gl_Vertex;
  
	gl_Position = ftransform();
	pos = (gl_Vertex * gl_ModelViewMatrix).xyz;
    
    gl_FrontColor = gl_Color;
    norm = (vec4(gl_Normal,1) * gl_ModelViewMatrix).xyz;
}
