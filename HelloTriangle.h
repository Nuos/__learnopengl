#pragma once
#include <glew.h>
#include <glfw3.h>

#define _HelloTriangle_
#ifdef _HelloTriangle_

class HelloTriangle
{
public:
    static int enter();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif//_HelloTriangle_
