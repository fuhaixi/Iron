#version 330 core
out vec4 FragColor;
in vec2 uv;
in vec4 color;
in vec3 normal;
in mat3 TBN;
in vec4 frag_pos_light_space;
in vec3 frag_pos;



uniform vec3 light_dir;
uniform sampler2D albedo;
uniform sampler2D shadow_map;
uniform sampler2D normal_map;

uniform vec3 light_color;
uniform vec3 ambient;
uniform vec3 camera_pos;

float isInShadow(vec3 N, vec3 L){
    vec3 ndc = frag_pos_light_space.xyz/frag_pos_light_space.w;
    ndc = ndc*.5 + .5;
    float current_depth = ndc.z;

    vec2 tex_size = 1.0/ textureSize(shadow_map,0);
    float bias = max(0.05*(1. - dot(N, L)), 0.005);

    float ret=0;
    for(int xi = -1; xi<=1; xi++){
        for(int yi = -1; yi<=1; yi++){
            float closest_depth = texture(shadow_map, ndc.xy+vec2(xi,yi)*tex_size).x;
            float w = 1.0 + 1.-abs(float(xi)) + 1.- abs(float(yi));
            ret += current_depth- bias > closest_depth? w: 0.;
        }
    }

    ret = ret/15;
    return ret;
    
}

void main(){
    //world space

    vec3 N = normalize(TBN * (texture(normal_map, uv).rgb *2. -1.));
    vec3 L = normalize(light_dir);
    vec3 R = reflect(-L, N);
    vec3 E = normalize(camera_pos - frag_pos);

    

    float diffuse = max(dot(N, L), 0.0);
    float specular = pow(max(dot(R,E),0.0), 5.);
    vec3 diffuse_color = diffuse * light_color;
    vec3 specular_color = specular * light_color *.5 ;
    

    vec3 Color = texture(albedo, uv).xyz * ((diffuse_color +specular_color)*(1.-isInShadow(N,L)) + ambient) ;
    FragColor = vec4(Color, 1.0);
    //FragColor = vec4(uv, 1.0, 1.0);
}