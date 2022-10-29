#version 410

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//attribute vec4 a_color;
//attribute vec2 texture_color;
//attribute vec3 aNormal;
//uniform vec3 lightPos;
//varying vec4 vertexColor;
//varying vec2 TexCoord;
//varying vec3 Normal;
//varying vec3 FragPos;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //    FragPos = vec3(modelMat * vec4(a_color.xyz, 1.0));
    //    gl_Position = projMat * viewMat * vec4(FragPos, 1.0f);
    //    Normal = (mat3(modelMat) * gl_NormalMatrix) * aNormal;
    //    Normal = gl_NormalMatrix * aNormal;
    //    TexCoord = texture_color;
    //    Normal = mat3(transpose(inverse_mat4(modelMat))) * aNormal;
}