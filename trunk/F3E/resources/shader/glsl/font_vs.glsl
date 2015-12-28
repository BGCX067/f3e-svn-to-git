#version 150 compatibility
#extension GL_ARB_explicit_attrib_location : enable
#pragma debug(on)

uniform mat4 Projection; 
uniform mat4 View; 
uniform mat4 World; 

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in vec4 InstPosition;
layout(location = 3) in vec4 Color;

out vec4 outColor;
out vec2 outTexCoord;

void main()
{	
	float size = 1.0f/16.0f;
	int row = int(InstPosition.z) / 16;
	int col = int(InstPosition.z) % 16;
	outTexCoord.xy = TexCoord / 16.0f;
	outTexCoord.x = outTexCoord.x + col*size;
	outTexCoord.y = outTexCoord.y + row*size;
	outTexCoord.y += 0.0045f;

	vec2 modPosition = Position;
	modPosition.xy = modPosition.xy  + InstPosition.xy;
	
	outColor = Color;

	gl_Position =   Projection * (World * View ) * vec4(modPosition.x, modPosition.y, 0, 1);
}
