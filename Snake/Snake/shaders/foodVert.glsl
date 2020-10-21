#version 400 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 projection;

float blah = 20.0; // arbitrary scale

// contiguous basis vectors
mat4 scale = mat4(blah, 0.0, 0.0, 0.0,  // 1. column
				  0.0, blah, 0.0, 0.0,  // 2. column
				  0.0, 0.0, blah, 0.0,  // 3. column
				  0.0, 0.0, 0.0, 1.0); // 4. column

void main()
{
	gl_Position =  projection * scale *  model * vec4(aPos, 1.0);
}