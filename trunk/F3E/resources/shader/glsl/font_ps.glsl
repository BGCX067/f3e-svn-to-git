#version 150 compatibility

uniform sampler2D my_color_texture;

out vec4 FragmentColor;

in vec4 outColor;
in vec2 outTexCoord;

void main()
{
	FragmentColor = texture2D(my_color_texture, outTexCoord) * outColor;
}
