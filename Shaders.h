#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glew.h>

class Shader
{
public:
    Shader(void);
    ~Shader();

    GLuint Program;
    Shader(const char* vertexPath, const GLchar* fragmentPath);
    void Use();
};
