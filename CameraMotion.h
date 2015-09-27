#pragma once

#if 1
#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
class CameraMotion
{
public:
    static void do_movement();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static int enter();
};
#endif
