//
// Created by 刘小备 on 2019/1/31.
//

#include "Shader.h"
Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    this->vertexPath = vertexPath;
    this->fragmentPath = fragmentPath;
    std::ifstream vertexSource;
    std::ifstream fragmentSource;
    vertexSource.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    fragmentSource.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    try {
        vertexSource.open(vertexPath,std::ios::in);
        fragmentSource.open(fragmentPath,std::ios::in);
        if(!vertexSource.is_open()||!fragmentSource.is_open()){
           throw std::exception();
        }
        std::stringstream vertexStream,fragmentStream;
        vertexStream << vertexSource.rdbuf();
        fragmentStream << fragmentSource.rdbuf();
        vertexSource.close();
        fragmentSource.close();
        vertexSourceCode = vertexStream.str().c_str();
        fragmentSourceCode = fragmentStream.str().c_str();
    }catch(std::exception & ex){
        std::cout<<ex.what()<<std::endl;
    }
    const char * vertexCode = vertexSourceCode.c_str();
    const char * fragmentCode = fragmentSourceCode.c_str();
    unsigned int vertexShader;
    glewInit();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);
    checkCompilerError(vertexShader, "vertexShader");
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    checkCompilerError(fragmentShader, "fragmentShader");
    ID = glCreateProgram();
    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);
    glLinkProgram(ID);
    checkCompilerError(ID,"PROGRAM");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::checkCompilerError(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::Shader() {}

//Shader& Shader::operator=(Shader &shader) {
//
//}
