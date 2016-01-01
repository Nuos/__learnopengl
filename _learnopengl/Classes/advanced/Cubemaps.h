#pragma once
#define _CubeMaps_H_
#ifdef _CubeMaps_H_

#include <glew.h>
#include <glfw3.h>
#include <vector>
class Cubemaps
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void Do_Movement();
    static GLuint loadTexture(GLchar* path);
    static GLuint loadCubemap(std::vector<const GLchar*> faces);

    /*static GLuint loadTexture(GLchar* path, GLboolean alpha = false);
    static GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);*/
    static int enter();
};

#endif//_CubeMaps_H_