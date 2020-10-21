#version 410 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoord;

uniform mat4 projection;

void main()
{
    TexCoord = texCoords;
    gl_Position = projection * vec4(vertex, 0.0, 1.0);
}