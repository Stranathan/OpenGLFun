#version 400 core

out vec4 fragColor;

uniform float time;
uniform vec2 resolution;
uniform int linkIndex;

void main()
{
	vec3 col = vec3(1., 0.2, 0.1) + vec3(0.8, 0.5, 0.5) * clamp(cos(5. * (time - 4.08 * float(linkIndex))), 0., 1.);; 
	fragColor = vec4(col, 1.0);
}