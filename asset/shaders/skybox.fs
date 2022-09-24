#version 330 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;
in vec3 tex_coord;

uniform samplerCube sky_box;
uniform float energy;

void main(){
    FragColor = texture(sky_box, tex_coord)*energy;
    BrightColor = vec4(0);
}