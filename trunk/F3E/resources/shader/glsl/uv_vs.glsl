#version 150 compatibility
#extension GL_ARB_explicit_attrib_location : enable

uniform mat4 Projection; 
uniform mat4 View; 
uniform mat4 World; 

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

void main()
{	
	gl_TexCoord[0].xy = TexCoord;
	
	int row = gl_InstanceID / 40;

	vec4 modPosition = Position + vec4( gl_InstanceID%40 * 1.1f, row * 1.1f, 0,1);
	modPosition.xy = modPosition.xy - vec2(20,20);
	mat4 ModelView = View * World;
	gl_Position =  Projection * ModelView * modPosition;
}
