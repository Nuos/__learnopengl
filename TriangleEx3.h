#pragma once
#define _TriangleEx_
#ifdef _TriangleEx_

#include <glew.h>
#include <glfw3.h>
class TriangleEx
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static int enter();
};

#endif//_TriangleEx_
