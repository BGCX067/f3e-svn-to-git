#version 150 compatibility

out vec4 FragmentColor;

void main()
{
	FragmentColor.rg = gl_TexCoord[0].st;
}
