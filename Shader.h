//
// Created by 刘小备 on 2019/1/31.
//

#ifndef TEST_SHADER_H
#define TEST_SHADER_H
#include <glew.h>
#include <glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Material.h"
class Shader {
public:
    Shader(const char * vertexPath,const char * fragmentPath);

    const char * vertexPath;
    const char * fragmentPath;
    Shader();
    std::string vertexSourceCode;
    std::string fragmentSourceCode;
    unsigned int ID;
    void checkCompilerError(GLuint shader, std::string type);
};


#endif //TEST_SHADER_H
