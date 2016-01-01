#pragma once
//#define _Coord_H_
#ifdef _Coord_H_

#include <glew.h>
#include <glfw3.h>

class Coord
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static int enter();
};

#endif//_Coord_H_