
varying vec2 uv;
void main()
{
	gl_Position = ftransform();
    uv = (gl_Position.xy + vec2(1,1)) / 2.0;
}