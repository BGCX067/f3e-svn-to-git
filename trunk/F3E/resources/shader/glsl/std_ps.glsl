#version 150 compatibility

uniform sampler2D my_color_texture;

out vec4 FragmentColor;

void main()
{
	FragmentColor = texture2D(my_color_texture, gl_TexCoord[0].st);
}
