#version 410
out vec4 FragColor;
//struct Material{
//    vec3 ambient;
//    sampler2D diffuse;
//    sampler2D specular;
//    float Shininess;
//};
//
//uniform vec4 outcolor;
//uniform vec3 lightColor;
//uniform vec3 lightPos;
//uniform vec3 viewPos;
//uniform Material material;
//varying vec4 vertexColor;
//varying vec2 TexCoord;
//varying vec3 Normal;
//varying vec3 FragPos;


void main(){
    FragColor = vec4(0, 0, 0, 0);
    //    vec3 ambient =lightColor * texture2D(material.diffuse, TexCoord).rgb;
    //    vec3 norm = normalize(Normal);
    //    vec3 lightDir = normalize(lightPos-FragPos);
    //    float diff = max(dot(lightDir,norm), 0.0);
    //    vec3 diffuse = lightColor * diff * texture2D(material.diffuse,TexCoord).rgb;
    //
    //
    //    float specularStrength = 0.5;
    //    vec3 viewDir = normalize(viewPos - FragPos);
    //    vec3 reflectDir = reflect(-lightDir, norm);
    //    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.Shininess);
    //    vec3 specular = lightColor * spec * texture2D(material.specular,TexCoord).rgb;
    //
    //    vec3 result = ambient + diffuse + specular;
    //    gl_FragColor = vec4(1.0,1.0,1.0,1.0);
    //    texture2D(ourTexture,TexCoord);
    //    linearly interpolate between both textures (80% container, 20% awesomeface)
    //    gl_FragColor = mix(texture2D(ourTexture,TexCoord), texture2D(ourFace,TexCoord), 0.2) * vec4(result, 1.0);
}