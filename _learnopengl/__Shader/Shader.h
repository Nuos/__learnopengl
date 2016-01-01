#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glew.h>

class Shader
{
public:
    GLuint Program;

    //////////////////////////////////////////////////////////////////////////
    // Reading From File
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
    {
        // retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // ensures ifstream objects can throw exceptions
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // close file handlers
            vShaderFile.close();
            fShaderFile.close();

            // convert stream into GLchar array..
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure* /*e*/)
        {
            std::cout << "Error:Shader:File_not_successfully_read....\n";
        }
        if (true) {
            std::cout << "===================================================================\n";
            std::cout << "[vertex  -shader-path]\n" << vertexPath 
                      << "\nvertex  Code\n" <<vertexCode<<"\n\n";
            std::cout << "[fragment-shader-path]\n" << fragmentPath
                      << "\nragmentCode\n" <<fragmentCode << "\n\n";

            std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
        }

        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();

        // compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        ///////////////////
        // vertex-shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // error info. if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "Error:Shader:vertex_compilation_failed..\n" << infoLog << "\n";
        }

        ///////////////////
        // 
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // Print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "Error:Shader:fragment_compilation_failed..\n\n" << infoLog << std::endl;
        }
        ///////////////////
        // Shader Program
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);

        // error info. if any
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "Error:Shader_Program_linkage_failed...\n" << infoLog << std::endl;
        }

        // delete the shaders as they're linked into our program now and no longer necessary.
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    //////////////////////////////////////////////////////////////////////////
    //
    void Use()
    {
        glUseProgram(this->Program);
    }
};

#endif//_SHADER_H_