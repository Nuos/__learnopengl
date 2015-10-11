#pragma once
#define _BasicLight_
#ifdef _BasicLight_

#include <glew.h>
#include <glfw3.h>

class BasicLight
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void do_movement(void);
    static int enter();
};
#endif//_BasicLight_
