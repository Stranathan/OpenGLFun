#version 400 core

out vec4 fragColor;

uniform float time;
uniform vec2 resolution;
uniform int linkIndex;

void main()
{
	vec3 col = vec3(0.2, float(linkIndex) / 100., 0.1) + vec3(0.2, 0.5, 0.2) * clamp(sin(5. * (time - 10. * float(linkIndex))), 0., 1.);; 
	fragColor = vec4(col, 1.0);
}