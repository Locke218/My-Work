#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) uniform mat4 transform;
layout (location = 4) uniform mat4 cameraMat;
layout (location = 5) uniform vec3 lightLocation;
layout (location = 6) uniform vec3 camLocation;


out vec2 fragUV;
out vec3 fragLoc;
out vec3 fragNorm;
out vec3 lightLoc;
out vec3 camLoc;

void main()
{
	fragUV = uv;

	fragLoc = vec3(transform * vec4(position, 1));
	fragNorm = vec3(transpose(inverse(transform)) * vec4(normal, 0.0));

	lightLoc = lightLocation;
	camLoc = camLocation;

	gl_Position = cameraMat * transform * vec4(position, 1);
}