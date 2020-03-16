#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model; 

out vec3 OurColor;  
out vec2 terrainTexCoords;

void main()
{
    vec3 FragPos = vec3(vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(FragPos, 1.0);

    OurColor = 0.5f * normalize(aColor) + 0.5f;
    
    terrainTexCoords = texCoord;
}  