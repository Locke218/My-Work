#version 430

in vec3 lightLoc;
in vec3 camLoc;
in vec3 fragLoc;
in vec3 fragNorm;

in vec2 fragUV;
uniform sampler2D myTexture;

void main()
{
	vec3 l = normalize(lightLoc - fragLoc);
	vec3 v = normalize(camLoc - fragLoc);
	vec3 h = normalize(l + v);


	vec3 norm = normalize(vec3(fragNorm));

	float ambient = .3;
	float diffuse = .6 * max(dot(norm, l ), 0.0);
	float specular = .6 * pow(max(dot(norm, h), 0.0), 32);
	float brightness = ambient + diffuse + specular;

	vec4 texColor = texture(myTexture, fragUV);
	vec3 texColor2 = vec3(texColor * brightness);

	gl_FragColor = vec4(vec3(texColor * brightness), texColor.a);
}