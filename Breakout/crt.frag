/**
 By piyuhslayer
 ShaderToy: https://www.shadertoy.com/view/wld3WN
*/

#version 130

uniform sampler2D scene;
uniform float u_time;
uniform vec2 u_resolution;
uniform int u_frame;

// amount of seconds for which the glitch loop occurs
#define DURATION 5.
// percentage of the duration for which the glitch is triggered
#define AMT .5 

#define SS(a, b, x) (smoothstep(a, b, x) * smoothstep(b, a, x))

#define UI0 1597334673U
#define UI1 3812015801U
#define UI2 uvec2(UI0, UI1)
#define UI3 uvec3(UI0, UI1, 2798796415U)
#define UIF (1. / float(0xffffffffU))

// Hash by David_Hoskins
vec3 hash33(vec3 p)
{
	uvec3 q = uvec3(ivec3(p)) * UI3;
	q = (q.x ^ q.y ^ q.z)*UI3;
	return -1. + 2. * vec3(q) * UIF;
}

// Gradient noise by iq
float gnoise(vec3 x)
{
    // grid
    vec3 p = floor(x);
    vec3 w = fract(x);
    
    // quintic interpolant
    vec3 u = w * w * w * (w * (w * 6. - 15.) + 10.);
    
    // gradients
    vec3 ga = hash33(p + vec3(0., 0., 0.));
    vec3 gb = hash33(p + vec3(1., 0., 0.));
    vec3 gc = hash33(p + vec3(0., 1., 0.));
    vec3 gd = hash33(p + vec3(1., 1., 0.));
    vec3 ge = hash33(p + vec3(0., 0., 1.));
    vec3 gf = hash33(p + vec3(1., 0., 1.));
    vec3 gg = hash33(p + vec3(0., 1., 1.));
    vec3 gh = hash33(p + vec3(1., 1., 1.));
    
    // projections
    float va = dot(ga, w - vec3(0., 0., 0.));
    float vb = dot(gb, w - vec3(1., 0., 0.));
    float vc = dot(gc, w - vec3(0., 1., 0.));
    float vd = dot(gd, w - vec3(1., 1., 0.));
    float ve = dot(ge, w - vec3(0., 0., 1.));
    float vf = dot(gf, w - vec3(1., 0., 1.));
    float vg = dot(gg, w - vec3(0., 1., 1.));
    float vh = dot(gh, w - vec3(1., 1., 1.));
	
    // interpolation
    float gNoise = va + u.x * (vb - va) + 
           		u.y * (vc - va) + 
           		u.z * (ve - va) + 
           		u.x * u.y * (va - vb - vc + vd) + 
           		u.y * u.z * (va - vc - ve + vg) + 
           		u.z * u.x * (va - vb - ve + vf) + 
           		u.x * u.y * u.z * (-va + vb + vc - vd + ve - vf - vg + vh);
    
    return 2. * gNoise;
}


// gradient noise in range [0, 1]
float gnoise01(vec3 x)
{
	return .5 + .5 * gnoise(x);   
}

// warp uvs for the crt effect
vec2 crt(vec2 uv)
{
    float tht  = atan(uv.y, uv.x);
    float r = length(uv);
    // curve without distorting the center
    r /= (1. - .1 * r * r);
    uv.x = r * cos(tht);
    uv.y = r * sin(tht);
    return .5 * (uv + 1.);
}

// Reference: https://waelyasmina.net/articles/9-hands-on-glsl-examples-for-shader-newbies/#example_5
//mat2 scale(vec2 scale) {
//    return mat2(scale.x, 0., 0., scale.y);
//}


void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution;
    //uv *= scale(vec2(0.5));
    float t = u_time;
    
    // smoothed interval for which the glitch gets triggered
    float glitchAmount = SS(DURATION * .001, DURATION * AMT, mod(t, DURATION));  
	float displayNoise = 0.;
    vec3 col = texture(scene, uv).rgb;
    vec2 eps = vec2(5. / u_resolution.x, 0.);
    vec2 st = vec2(0.);

	uv = crt(uv * 2. - 1.); // warped uvs
    ++displayNoise;

    // analog distortion
    float y = uv.y * u_resolution.y;
    float distortion = gnoise(vec3(0., y * .01, t * 500.)) * (glitchAmount * 4. + .1);
    distortion *= gnoise(vec3(0., y * .02, t * 250.)) * (glitchAmount * 2. + .025);

    // white noise + scanlines
    displayNoise = clamp(displayNoise, 0., 1.);
    //col += (.15 + .65 * glitchAmount) * (hash33(vec3(gl_FragCoord, mod(float(t /* Used to be 'iFrame'*/), 1000.))).r) * displayNoise;
    col += (.15 + .65 * glitchAmount) * (hash33(vec3(gl_FragCoord.xy, mod(float(u_frame), 1000.))).r) * displayNoise;
    col -= (.25 + .75 * glitchAmount) * (sin(4. * t + uv.y * u_resolution.y * 1.75)) * displayNoise;

    //crt vignette (from https://www.shadertoy.com/view/Ms23DR)
    float vig = 8.0 * uv.x * uv.y * (1.-uv.x) * (1.-uv.y);
	col *= vec3(pow(vig, .25)) * 1.5;
    if(uv.x < 0. || uv.x > 1.) col *= 0.;

    gl_FragColor = vec4(col, 1.0);
}