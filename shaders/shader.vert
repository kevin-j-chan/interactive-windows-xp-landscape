#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 TexCoords;
out vec3 OurColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model; 


void main()
{
    TexCoords = aPos;
    OurColor = 0.5f * normalize(aColor) + 0.5f;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}  