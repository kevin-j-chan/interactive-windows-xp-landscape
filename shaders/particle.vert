#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
out vec2 TexCoords;
out vec4 ParticleColor;

uniform vec3 offset;
uniform vec4 color;
uniform mat4 projection;

void main()
{
    float scale = 1.0f;
    TexCoords = tex;
    ParticleColor = vec4(1,0,0,1);
    gl_Position = projection * vec4((vertex * scale) + offset, 1.0);
}