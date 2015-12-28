#version 150 compatibility

uniform sampler2D my_color_texture;

void main (void)
{
	vec3 bump = normalize( texture2D(my_color_texture, gl_TexCoord[0].xy).xyz * 2.0 - 1.0);

	
	gl_FragColor = vec4(bump,1);
}