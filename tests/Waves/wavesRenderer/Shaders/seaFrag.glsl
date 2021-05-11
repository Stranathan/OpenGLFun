#version 410 core

out vec4 fragColor;

uniform float iTime;
uniform float waveTimer;
uniform vec2 iResolution;
uniform vec2 iMouse;

#define point1 (0.7)
#define point2 (0.2)
#define waveTimer2 (0.0)

float when_eq(float x, float y) 
{
  return 1.0 - abs(sign(x - y)); // return 1. iff x == y
}

float when_gt(float x, float y) 
{
	return max(sign(x - y), 0.0);
}
void main()
{	
	vec2 uv = 2. * gl_FragCoord.xy/iResolution.xy - 1.;
    uv.x *= iResolution.x/iResolution.y;
    uv.y += 0.7;
    
    vec2 mousePos = iMouse;
	mousePos.x *= iResolution.x/ iResolution.y;
   
    float gaussian1 = .4 * exp(-15. * pow((uv.x - mousePos.x) - 1. * waveTimer, 2.0));
    float gaussian2 = abs(sin(iTime)) * .8 * exp(-15. * pow((uv.x + point2), 2.0));
    
    float derGaussian = gaussian1 + gaussian2;
    
    float val = 1. - smoothstep(derGaussian, derGaussian + 0.02, uv.y);
    
    vec3 col = vec3(0.3,0.6,0.9) * val;

    // transparent except where mask is with some functional softening:
    fragColor = vec4(col, when_gt(val, .7));
}