#version 330 core


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in float sNum;
layout (location = 3) in float edge;


uniform mat4 projection;
uniform mat4 modelview;

out vec3 colorV;
out float surfaceNumber;
out float isEdge;
out vec3 pos;
out float sampleExtraOutput;

void main()
{
    gl_Position = projection * modelview * vec4(position, 1.0);
    surfaceNumber = sNum;
    isEdge = edge;
    colorV = 0.5f * normalize(vertColor);
    //colorV = normalize(vertColor);
    //colorV = vertColor;
    sampleExtraOutput = 1.0f;
} 