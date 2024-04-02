//---------------------------------------
#shader Vertex

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aTexCoord;

out vec3 vColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
//---------------------------------------
#shader Fragment

#version 330 core
out vec4 FragColor;

in vec3 vColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor =  mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}