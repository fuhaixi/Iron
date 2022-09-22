#version 330 core
out vec4 FragColor;
in vec3 tex_coord;

uniform samplerCube sky_box;

void main(){
    FragColor = texture(sky_box, tex_coord);
}