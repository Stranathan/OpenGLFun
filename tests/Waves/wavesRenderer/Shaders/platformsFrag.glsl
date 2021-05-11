#version 410 core

in vec2 TexCoord;

out vec4 fragColor;

uniform float iTime;
uniform vec2 iResolution;
uniform sampler2D textureSample;

void main()
{
	// Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/iResolution.xy;

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
	fragColor = texture(textureSample, TexCoord) * vec4(col, 1.0);
}