#version 330 core

in vec3 OurColor;
in vec2 terrainTexCoords;

uniform sampler2D tex;

uniform bool drawTerrain;

out vec4 FragColor;

void main()
{    
    vec3 result = OurColor;

    FragColor = texture(tex, terrainTexCoords) * vec4(result, 1.0);
}