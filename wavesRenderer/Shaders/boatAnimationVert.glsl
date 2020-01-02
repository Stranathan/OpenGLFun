#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float iTime;

void main()
{
	gl_Position = vec4(aPos, 1.0);

	ourColor = aColor;
	float index = mod(floor(14. * iTime), 9.);
	float numRows = 3.;
	float xOffset = mod(index, numRows) * 1./numRows ;
	float yOffset = ((numRows - 1.) - floor(index / numRows)) * 1./numRows;
	TexCoord = (aTexCoord * 1./numRows) + vec2(xOffset, yOffset);
}
