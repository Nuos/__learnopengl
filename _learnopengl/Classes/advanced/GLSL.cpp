#include "GLSL.h"
#ifdef _GLSL_H_

#include <SOIL.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <glm/gtc/type_ptr.hpp>


//Properties
GLuint screenWidth = 800, screenHeight = 600;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = screenWidth * 0.5F;
GLfloat lastY = screenHeight * 0.5F;
bool firstMode = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;




int GLSL::enter()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Advanced GLSL LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);


    Shader shaderRed("../_ShaderSource/advanced/ubo.vs", "../_ShaderSource/advanced/uboRed.frag");
    Shader shaderGreen("../_ShaderSource/advanced/ubo.vs", "../_ShaderSource/advanced/uboGreen.frag");
    Shader shaderBlue("../_ShaderSource/advanced/ubo.vs", "../_ShaderSource/advanced/uboBlue.frag");
    Shader shaderYellow("../_ShaderSource/advanced/ubo.vs", "../_ShaderSource/advanced/uboYellow.frag");

     #pragma region "object_initialization"

    GLfloat cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f
    };

    // Setup cube VAO
    GLuint cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); 
    glBindVertexArray(0);

    #pragma endregion

    // create a uniform buffer object
    // first we get the relevant block indices
    GLuint uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.Program, "Matrices");
    GLuint uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.Program, "Matrices");
    GLuint uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.Program, "Matrices");
    GLuint uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.Program, "Matrices");

    // then we link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(shaderRed.Program, uniformBlockIndexRed, 0);
    glUniformBlockBinding(shaderGreen.Program, uniformBlockIndexGreen, 0);
    glUniformBlockBinding(shaderBlue.Program, uniformBlockIndexBlue, 0);
    glUniformBlockBinding(shaderYellow.Program, uniformBlockIndexYellow, 0);

    // now actually create the buffer
    GLuint uboMatrices;
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point...
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix
    glm::mat4 projection = glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    // game loop
    while (!glfwWindowShouldClose(window)) {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //////////////////////////////////////////////////////////////////////////
        // set the view and projection matrix in the uniform block
        glm::mat4 view = camera.GetViewMatrix();
        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        // draw 4 cubes
        //RED
        glBindVertexArray(cubeVAO);
        shaderRed.Use();
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderRed.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        ////GREEN
        //shaderGreen.Use();
        //model = glm::mat4();
        //model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shaderGreen.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        ////BLUE
        //shaderBlue.Use();
        //model = glm::mat4();
        //model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shaderBlue.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        ////
        //shaderYellow.Use();
        //model = glm::mat4();
        //model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shaderYellow.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}


#pragma region "User input"
void GLSL::Do_Movement()
{
    if (keys[GLFW_KEY_W]) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S]) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A]) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D]) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void GLSL::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (action == GLFW_PRESS) {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void GLSL::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMode) {
        lastX = xpos;
        lastY = ypos;
        firstMode = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

#pragma endregion

#endif// _GLSL_H_