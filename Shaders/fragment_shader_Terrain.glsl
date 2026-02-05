#version 330 core

// Ouput data
out vec4 color;
in vec3 vertices_position_fragment;
in vec3 vertices_normals_fragment;
in vec2 vertices_texCoord_fragment;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform mat4 model;
uniform mat4 view;

struct Material {
    vec3 albedo;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};

uniform Material material;


vec3 light_positions[5] = vec3[](
    vec3(0.0, 100, 1.0),
    vec3(0.0, 100, 20.0),
    vec3(0.0, 100, 40.0),
    vec3(0.0, 100, 70.0),
    vec3(0.0, 100, 100.0)
);
const vec4 light_color_power = vec4(1, 1, 1.0, 2000);

void main(){
    vec4 c;
    if(vertices_position_fragment.y < 0.5){
        float d0 = vertices_position_fragment.y*2;
        float d1 = (0.5-vertices_position_fragment.y)*2;
        c = d0 * texture(texture1, vertices_texCoord_fragment) + d1 * texture(texture0, vertices_texCoord_fragment);
    }
    else{
        float d0 = (vertices_position_fragment.y-0.5)*2;
        float d1 = (1-vertices_position_fragment.y)*2;
        c = d0 * texture(texture2, vertices_texCoord_fragment) + d1 * texture(texture1, vertices_texCoord_fragment);
    }



//    vec3 N = normalize(vertices_normals_fragment);
//    vec3 cameraPos = vec3(inverse(view)[3]);
//    vec3 V = normalize(cameraPos - vertices_position_fragment);
//    vec3 ambient = material.ambient * c.xyz;

//    vec3 baseColor = ambient;

//    for(int i = 0; i < 5; i ++){
//        vec3 L = light_positions[i] - vertices_position_fragment;
//        float distance = length(L);
//        L = normalize(L);

//        //diffuse
//        float NdotL = max(dot(N, L), 0.0);
//        vec3 diffuse = material.diffuse * NdotL * c.xyz;

//        //specular
//        vec3 H = normalize(L + V);
//        float NdotH = max(dot(N, H), 0.0);
//        float spec = pow(NdotH, material.shininess);
//        vec3 specular = material.specular * spec * light_color_power.rgb;

//        float attenuation = light_color_power.a / (distance * distance);

//        baseColor += (diffuse + specular) * light_color_power.rgb * attenuation;

//    }
    color = c;
}
