#version 150 compatibility
#extension GL_ARB_explicit_attrib_location : enable


uniform mat4 Projection; 
uniform mat4 View; 
uniform mat4 World; 

layout(location = 0) in vec4 Position;

void main()
{	
	gl_Position =  Projection * (View * World) * Position;
}
