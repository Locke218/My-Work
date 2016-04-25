#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) uniform mat4 transform;

out vec2 fragUV;

void main()
{
	fragUV = uv;
	//fragUV = uv;
	gl_Position = transform * vec4(position, 1);
}