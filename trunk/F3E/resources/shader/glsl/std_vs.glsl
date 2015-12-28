#version 150 compatibility
#extension GL_ARB_explicit_attrib_location : enable

//layout(triangles) in;

//varying vec3 normal, lightDir;
uniform mat4 Projection; 
uniform mat4 View; 
uniform mat4 World; 

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
//in vec4 InVertex;  //w will be set to 1.0 automatically
//in vec2 InTexCoord0;


void main()
{	
	gl_TexCoord[0].xy = TexCoord;

	mat4 ModelView = View * World;
	gl_Position =  Projection * ModelView * Position;
}
