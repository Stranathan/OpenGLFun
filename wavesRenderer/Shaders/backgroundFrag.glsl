#version 410 core

out vec4 fragColor;

uniform float iTime;
uniform vec2 iResolution;

void main()
{	
	vec2 uv = (2.0*gl_FragCoord.xy -iResolution.xy) / iResolution.y; 
    
    float xVal = smoothstep(0.01, 0.01 + 0.005, fract(5. * uv.x));
    float yVal = smoothstep(0.01, 0.01 + 0.005, fract(5. * uv.y));
    float gridCol = (1. - (xVal * yVal));
    
    float offset = 0.07 * sin(iTime);
    float stop1 = -0.2 + offset;
    float stop2 = -0.1 + offset;
    float stop3 = 0.9;
    
    vec3 col1=vec3(0.3,0.4,0.9);
    vec3 col2=vec3(0.9);
    vec3 col3=vec3(0.15,0.6,0.8);
       
    vec3 col = mix(col1,col2,smoothstep(stop1, stop2,uv.y));
    col = mix(col,col3,smoothstep(stop2,stop3,uv.y));
    
    col *= (1. - gridCol);
    col += gridCol * vec3(0.6, 0.6, 0.6);
    fragColor = vec4(col, 1.0);
}