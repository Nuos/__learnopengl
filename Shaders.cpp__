#include "Shader.h"

//GLuint Program;
Shader::Shader()
{
}

Shader::~Shader()
{
}

Shader::Shader(const char* vertexPath, const GLchar* fragmentPath)
{
    // retrieve the vertex/fragment source code from filepath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensures ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if (true) {
            printf("\n==============================================\n");
            printf("\t <vertexShader>\n\t %s\n", vertexCode.c_str());
            printf("\n==============================================\n");
            printf("\t <fragmentShader>\n\t %s\n", fragmentCode.c_str());
            printf("\n==============================================\n");
        }
    }
    catch (std::ifstream::failure e) {
        std::cout << "Error::Shader::File_not_Successfully_Read..\n\n";
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    // compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Error:Shader::Vertex::Compilation_Failed.\n" << infoLog << "\n\n";
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any..
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "Error:Shader::Fragment::Compilation_Failed..\n\n" << infoLog << "\n\n";
    }

    // shader program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);

    // print linking errors if any.
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "Error:Shader::Program::Linking_Failed..\n\n" << infoLog << "\n\n";
    }

    // delete the shaders as they're linked into our program now and no longer necessary..
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(this->Program);
}
