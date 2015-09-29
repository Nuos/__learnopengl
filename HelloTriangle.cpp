#include <hellotriangle.h>

#ifdef _HelloTriangle_
#include <iostream>
const GLuint WIDTH = 800, HEIGHT = 600;

/* " The vertex shader allows us to specify any input we want in the form of vertex attributes
 *   and while this allows for great flexibility, 
 *   it does mean we have to manually specify what part of our input data goes 
 *   to which vertex attribute in the vertex shader."
 */
const size_t locationPos/**/ = 15;// value ranging from [0, 15] is valid.!!!!!!!!!!!!!
const GLchar* vertexShaderSource =
"#version 330 core\n\
//layout (location = 0) in vec3 position;\n\
layout (location/**/ = 15) in vec3 position;\n\ ////*********************
void main()\n\
{\n\
gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n\
}\n\0";
const GLchar* fragmentShaderSource =
"\n#version 330 core\n\
out vec4 color;\n\
void main()\n\
{\n\
color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
}\n\0";


int HelloTriangle::enter()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL...", nullptr, nullptr);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, WIDTH, HEIGHT);

    //////////////////////////////////////////////////////////////////////////
    // build and compile our shader program
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //////////////////////////////////////////////////////////////////////////
    // register VBO as the currently bound vertex buffer object

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(locationPos/**/, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);////*****************
    //glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(locationPos/**/);////***********************
    glBindBuffer(GL_ARRAY_BUFFER, 0);// unbind VBO
    glBindVertexArray(0);// unbind VAO

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void HelloTriangle::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

#endif// _HelloTriangle_
