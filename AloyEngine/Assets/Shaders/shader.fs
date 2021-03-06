#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
in mat3 TBN;

uniform vec3 viewPos; 


struct PointLight
{
    vec3 lightPos; 
    vec3 lightColor;
};

uniform PointLight lights[10];
uniform int pointLightCount;

uniform vec3 objectColor;

uniform int albedoCount;
uniform sampler2D texture_diffuse[2];

uniform int specularCount;
uniform sampler2D texture_specular[2];

uniform int normalCount;
uniform sampler2D texture_normal[2];

vec3 getAlbedo()
{
    if(albedoCount != 0)
        return texture(texture_diffuse[0], TexCoords).xyz;
    else
        return objectColor;
}
vec3 getNormal()
{
    if(normalCount == 0)
        return normalize(Normal);

    vec3 normal_rgb = texture(texture_normal[0], TexCoords).rgb; 
    normal_rgb = normalize(normal_rgb * 2.0 - 1.0); 
    normal_rgb = normalize(TBN * normal_rgb); 
    return normal_rgb; 
}
void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 norm = getNormal();
    vec3 result = vec3(0);
    for(int i =0; i<pointLightCount; ++i)
    {
        vec3 lightDir = normalize(lights[i].lightPos - FragPos);

        // ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lights[i].lightColor;
        
        // diffuse 
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].lightColor;
        
        // specular
        float specularStrength = 0.5;
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lights[i].lightColor;  
            
        result += (ambient + diffuse + specular) * getAlbedo();
    }
    FragColor = vec4(result, 1.0);
} 