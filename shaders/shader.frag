#version 330 core

in vec3 OurColor;
in vec2 terrainTexCoords;

in vec3 dirLightDirection;

uniform sampler2D tex;

uniform bool drawTerrain;

out vec4 FragColor;

// Lighting stuff
in vec3 normal;
in vec3 FragPos;

struct Material {

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
    vec3 color;
};  

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform Material material;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  


void main()
{   
  
    vec3 result = OurColor;

    /* REMOVE FROM HERE FOR LIGHT STUFF */
    vec3 ambient = material.ambient;
  	            
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    result *= 0.7;

    result += CalcDirLight(dirLight, norm, viewDir);        
    /* REMOVE UP TO HERE FOR LIGHT STUFF */

    FragColor = texture(tex, terrainTexCoords) * vec4(result, 1.0);
    
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-dirLightDirection);
   
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   
    vec3 ambient  = material.ambient;
    vec3 diffuse  = diff * material.diffuse;
    vec3 specular = spec * material.specular;
    return (ambient + diffuse + specular);
}  