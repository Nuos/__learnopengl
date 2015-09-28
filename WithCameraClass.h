#pragma once
#define __With_Camera_Class__
#ifdef __With_Camera_Class__

#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>

class WithCameraClass
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void Do_Movement();
    static int enter();
};
#endif//__With_Camera_Class__
