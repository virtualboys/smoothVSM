varying vec4 v_position;

void main()
{
    gl_Position = ftransform();
    //gl_Position = gl_Vertex
    v_position = gl_Position;
    
}