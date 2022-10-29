#version 410

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;


struct DirectionLight{
    vec3 angle;

    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
};

struct PointLight{
    vec3 Position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//uniform vec3 lightColor;
//uniform vec3 lightPos;
uniform sampler2D texture_diffuse;
uniform vec3 viewPos;

uniform DirectionLight directionLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
vec3 calculateDirectional(DirectionLight light, vec3 uNormal, vec3 dirToCamera){
    //diffuse
    float diffIntencity = max(dot(light.angle, uNormal), 0.0);
    vec3 diffuse = light.diffuse * diffIntencity;
    //specular
    float specularStrength = 0.2;
    vec3 reflectVec = reflect(light.angle, uNormal);
    float specularIntencity = pow(max(dot(reflectVec, dirToCamera), 0.0), 32.0);
    vec3 specular = light.specular * specularIntencity * specularStrength;
    //ambient
    vec3 ambient = light.ambient;
    //result
    return (specular + diffuse + ambient);
}

vec3 calculatePointLight(PointLight light, vec3 uNormal, vec3 dirToCamera){
    //diffuse
    vec3 dirToLight = normalize(light.Position - FragPos);
    float diffuseIntencity = max(dot(dirToLight, uNormal),0.0);
    vec3 diffuse = light.diffuse * diffuseIntencity;
    //specular
    float specularStrength = 0.5;
    vec3 reflectVec = reflect(-dirToLight, uNormal);
    float specularIntencity = pow(max(dot(reflectVec, dirToCamera), 0.0), 32.0);
    vec3 specular = light.specular * specularIntencity * specularStrength;
    //ambient
    vec3 ambient = light.ambient;
    //result
    float distance = length(light.Position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    specular *= attenuation;
    diffuse *= attenuation;
    return (specular + diffuse + ambient);
}

vec3 calculateSpotLight(SpotLight light, vec3 uNormal, vec3 dirToCamera){
    //diffuse
    vec3 dirToLight = normalize(light.position - FragPos);
    float diffuseIntencity = max(dot(dirToLight, uNormal),0.0);
    vec3 diffuse = light.diffuse * diffuseIntencity;
    //specular
    float specularStrength = 0.5;
    vec3 reflectVec = reflect(-dirToLight, uNormal);
    float specularIntencity = pow(max(dot(reflectVec, dirToCamera), 0.0), 32.0);
    vec3 specular = light.specular * specularIntencity * specularStrength;
    //ambient
    vec3 ambient = light.ambient;
    //result
    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(dirToLight, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (specular + diffuse + ambient);
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 cameraVec = normalize(viewPos - FragPos);
    vec3 result = calculateDirectional(directionLight, norm, cameraVec);
    result += calculatePointLight(pointLight, norm, cameraVec);
    result += calculateSpotLight(spotLight, norm, cameraVec);
    FragColor = texture(texture_diffuse, TexCoords) * vec4(result,1.0);
}
//    float diffuseIntencity = max(dot(norm, dirToLight), 0.0);
//    vec3 diffuse = diffuseIntencity * lightColor;
//    vec3 cameraVec = normalize(viewPos - FragPos);
//    vec3 reflectVec = reflect(-dirToLight,norm);
//    float specularIntencity = pow(max(dot(cameraVec, reflectVec),0.0),16.0);
//    vec3 specular = specularIntencity * lightColor;
//    vec3 result = (1.0,0.5,0.5) + diffuse + specular;
//    FragColor = texture(texture_diffuse, TexCoords) * vec4(result,1.0);
