#pragma once
//#define _HelloTriangle_
#ifdef _HelloTriangle_

#include <glew.h>
#include <glfw3.h>

class HelloTriangle
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static int enter();
};

#endif//_HelloTriangle_