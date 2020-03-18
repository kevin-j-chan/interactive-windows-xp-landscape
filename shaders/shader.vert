#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model; 
uniform float time;

out vec3 OurColor;
out vec2 terrainTexCoords;  

out vec3 normal;
out vec3 FragPos;

out vec3 dirLightDirection;

void main()
{
    vec3 FragPos = vec3(vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(FragPos, 1.0);

    OurColor = 0.5f * normalize(aNormal) + 0.5f;
    normal = mat3(transpose(inverse(model))) * aNormal;
    
    dirLightDirection = vec3(0.0, sin(time * 0.01), cos(time * 0.01));
    terrainTexCoords = texCoord;
}  