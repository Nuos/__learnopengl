/******
  source website of which is great mind:
    http://www.learnopengl.com/#!Getting-started/Camera
    
    
  GLfloat glfwGetTime();
    this function returns the time in seconds since GLFW is initialized.
    Unless the timer has explicitly been set with glfwSetTime,
    the timer measures tiem elapsed since the call to glfwInit.
    
    Could be used for calculating deltatime in which rendering the frame.
      GLfloat currentFrame = glfwGetTime();
      GLfloat lastFrame;
      GLfloat deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;
      
************************/
#pragma once

#define __CameraMotionSpeed_
#ifdef __CameraMotionSpeed_

#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
class CameraMotionSpeed
{
public:
    static void do_movement();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static int enter();
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};
#endif // __CameraMotionSpeed_
