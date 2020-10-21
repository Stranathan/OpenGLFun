#version 400 core

out vec4 fragColor;

uniform float time;
uniform vec2 resolution;
uniform vec3 pos;

// making life hard, one script at a time
float when_gt(float x, float y) 
{
	return max(sign(x - y), 0.0);
}
float when_lt(float x, float y) 
{
  return max(sign(y - x), 0.0);
}
float when_ge(float x, float y) 
{
	return 1.0 - when_lt(x, y);
}

void main()
{
	vec2 uv = 2. * (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;
    
	vec2 pseudoRes = vec2(25.0, 20.0);
	vec2 correctionOffset = vec2(12.5 - pos.x / 2., 10 - pos.y / 2.);
	vec2 magicPos = pos.xy + correctionOffset;
    vec2 mousePos = 2. * (magicPos - 0.5 * pseudoRes ) / 20.;

    vec3 col = vec3(0.1, 0.5, 0.93) * sin(length(100. * (uv - mousePos)) - 4. * time);
    fragColor = vec4(col, when_ge(col.r, 0.));
}