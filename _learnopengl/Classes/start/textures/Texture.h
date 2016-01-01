#pragma once
//#define _Texture_H_
#ifdef _Texture_H_

#include <glew.h>
#include <glfw3.h>

class Texture
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static int enter();
};
#endif//_Texture_H_