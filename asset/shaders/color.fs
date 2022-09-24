#version 330 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

uniform vec3 color;
void main(){
    //world space
    
    FragColor = vec4(color, 1.0);

    float brightness = dot(color, vec3(0.2126, 0.7152, 0.0722));
    brightness = step(1., brightness);

    BrightColor = vec4(brightness*color,1.);

}