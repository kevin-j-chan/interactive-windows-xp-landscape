#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 cloud_pos;
out vec3 fsun;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model; 
uniform float time = 0.0;

uniform bool pityPoints = false;

const vec2 data[4] = vec2[](
    vec2(-1.0,  1.0), vec2(-1.0, -1.0),
    vec2( 1.0,  1.0), vec2(1.0, -1.0));

void main()
{    
    if(pityPoints == true){
        gl_Position = vec4(data[gl_VertexID], 0.0, 1.0);
        cloud_pos = transpose(mat3(view)) * (inverse(projection) * gl_Position).xyz;
    }
    else {
        //gl_Position = projection * view * model * vec4(aPos, 1.0); //
        gl_Position = normalize(projection * view * model * vec4(aPos, 1.0));
        //cloud_pos = normalize(aPos);
        //cloud_pos = normalize(transpose(mat3(view)) * (inverse(projection) * gl_Position).xyz);
        cloud_pos = transpose(mat3(view)) * (inverse(projection) * gl_Position).xyz;
    
    }
    
    fsun = vec3(0.0, sin(time * 0.01), cos(time * 0.01));
}
