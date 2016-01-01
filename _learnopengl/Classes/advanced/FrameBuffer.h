//http://www.learnopengl.com/#!Advanced-OpenGL/Framebuffers
#pragma once
#define _FrameBuffer_H_
#ifdef _FrameBuffer_H_
#include <glew.h>
#include <glfw3.h>
class FrameBuffer
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void Do_Movement();
    static GLuint loadTexture(GLchar* path, GLboolean alpha = false);
    static GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
    static int enter();
};


#endif// _FrameBuffer_H_