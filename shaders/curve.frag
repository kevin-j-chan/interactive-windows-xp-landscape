/*#version 330 core

in float sampleExtraOutput;
in vec3 colorV;

out vec4 FragColor;

void main()
{
    FragColor = vec4(colorV, sampleExtraOutput);
} 
 */
 #version 330 core

in vec3 colorV;
in float sampleExtraOutput;
in float isEdge;

in float surfaceNumber;

out vec4 FragColor;

uniform float time = 0.0f;

void main()
{
	vec3 lightDir = vec3(0, 0, -20.0f);
	vec3 view = vec3(0, 0, -20.0f);
	float intensity;
	vec4 color;
	intensity = dot(lightDir,colorV);


	if(surfaceNumber < 1.01f){
		if (intensity > 10.2)
			color = vec4(0.0,.5,1.0,1.0);
		else if (intensity > 9.9)
			color = vec4(0.0,0.45,9.0,1.0);
		else if (intensity > 7.5)
			color = vec4(0.0,0.4,0.7,1.0);
		else if (intensity > 3.25)
			color = vec4(0.0,0.3,0.5,1.0);
		else
			color = vec4(0.0,0.2,0.35,1.0);
		FragColor = color;//vec4(colorV, 1.0f);
		
	}
	else if(surfaceNumber < 2.1f){

	if (intensity > 9.9)
			color = vec4(.9,0.8,0.0,1.0);
		else if (intensity > 7.5)
			color = vec4(0.8,0.64,0.0,1.0);
		else if (intensity > 3.25)
			color = vec4(0.6,0.48,0.0,1.0);
		else
			color = vec4(0.48,0.32,0.0,1.0);
		FragColor = color;//vec4(colorV, 1.0f);

	} 

	else if(surfaceNumber < 3.1f){

		if (intensity > 10.2)
			color = vec4(1.0,.3,.3,1.0);
		else if (intensity > 9.9)
			color = vec4(.9,.27,0.27,1.0);
		else if (intensity > 7.5)
			color = vec4(0.8,.25,0.25,1.0);
		else if (intensity > 3.25)
			color = vec4(0.6,.2,0.2,1.0);
		else
			color = vec4(0.5,.1,0.1,1.0);
		FragColor = color;//vec4(colorV, 1.0f);

	}
	else{

	if (intensity > 9.9)
			color = vec4(0.5,1.0,0.5,1.0);
		else if (intensity > 7.5)
			color = vec4(0.4,0.8,0.4,1.0);
		else if (intensity > 3.25)
			color = vec4(0.3,0.6,0.3,1.0);
		else
			color = vec4(0.2,0.4,0.2,1.0);
			FragColor = color;//vec4(colorV, 1.0f);

	} 

	if(isEdge > 10.0f){
	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}



}