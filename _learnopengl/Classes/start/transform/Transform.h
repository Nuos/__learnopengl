#pragma once
//#define _Transform_H_
#ifdef _Transform_H_

#include <glew.h>
#include <glfw3.h>

class Transform
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static int enter();
};

#endif//_Transform_H_