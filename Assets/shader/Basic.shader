//---------------------------------------
#shader Vertex

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
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