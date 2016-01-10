#pragma once
#define _GLSL_H_
#ifdef _GLSL_H_

#include <glew.h>
#include <glfw3.h>
#include <vector>
class GLSL
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void Do_Movement();

    static int enter();
};

#endif//_GLSL_H_