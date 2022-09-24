#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 uv;

uniform float exposure;
uniform float bloom;
uniform sampler2D screen_tex;
uniform sampler2D bloom_tex;
void main(){
    const float gamma = 2.2;
    vec3 col = texture(screen_tex, uv).rgb + texture(bloom_tex, uv).rgb*bloom;

    vec3 mapped = vec3(1.) - exp(-col*exposure);

    // mapped = pow(mapped, vec3(1./gamma));

    FragColor = vec4(mapped, 1.);
}