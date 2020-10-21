#version 410 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float iTime;
uniform float waveTimer;
uniform sampler2D texture1;
uniform sampler2D texture2;

float when_gt(float x, float y) 
{
  return max(sign(x - y), 0.0); // returns 1 if x > y; else returns 0;
}

float when_lt(float x, float y) 
{
  return max(sign(y - x), 0.0); // returns 1 if x < y; else 0;
}

void main()
{
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), abs(sin(iTime)));
	
	FragColor = texture(texture2, TexCoord);
}