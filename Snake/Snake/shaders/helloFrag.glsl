#version 400 core

out vec4 fragColor;
uniform float time;
uniform vec2 resolution;

mat3 rotAroundZ(float time)
{ 
    return mat3( cos(time), sin(time), 0.0,  // 1. column
				-sin(time), cos(time), 0.0,  // 2. column
				       0.0,       0.0, 1.0); // 3. column		 
}
void main()
{
	vec2 uv =  0.6 * ( gl_FragCoord.xy -.5 * resolution.xy ) / resolution.y;
	//vec3 shaderToyCol = 0.3 + 0.3*cos(time + uv.xyx + vec3(0,2,4) );
    
    vec3 uvVec3 = vec3(uv, 0.);
    uvVec3 = rotAroundZ(0.2 * time) * uvVec3;
    
    float modDivisor = 5.;
    uv = mod(uvVec3.xy, 1. / modDivisor);
    
    float verticalLines = smoothstep(0.5 / modDivisor, 0.51 / modDivisor, uv.x) -
                         (smoothstep(0.515 / modDivisor, 0.52 / modDivisor, uv.x));
    float horizontalLines = smoothstep(0.5 / modDivisor, 0.51 / modDivisor, uv.y) -
                           (smoothstep(0.515 / modDivisor, 0.52 / modDivisor, uv.y));

    float mask = clamp(verticalLines + horizontalLines, 0., 1.);
    vec3 col = (1. - mask) * 0.5 * vec3(.97, 0.98, 0.71); // shaderToyCol;
    fragColor = vec4(col,1.0);
}
