#pragma once
//#define _DiscardFrag_H_
#ifdef  _DiscardFrag_H_

#include <glew.h>
#include <glfw3.h>

class DiscardFrag
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void do_movement();
    static GLuint loadTexture(GLchar* path, GLboolean alpha = false);
    static int enter();
};

#endif//_DiscardFrag_H_