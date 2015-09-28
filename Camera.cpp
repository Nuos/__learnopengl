#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

    // constructor with Vectors
    Camera::Camera(glm::vec3 position/* = glm::vec3(0.0f, 0.0f, 0.0f)*/, glm::vec3 up/* = glm::vec3(0.0f, 1.0f, 0.0f)*/, GLfloat yaw/* = YAW*/, GLfloat pitch/* = PITCH*/)
        :Front(glm::vec3(0.0f, 0.0f, -1.0f))
        , MovementSpeed(SPEED)
        , MouseSensitivity(SENSITIVITY)
        , Zoom(ZOOM)
    {
        this->Position = position;
        this->WorldUp = up;
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }

    // constructor with scalar values
    Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0))
        , MovementSpeed(SPEED)
        , MouseSensitivity(SENSITIVITY)
        , Zoom(ZOOM)
    {
        this->Position = glm::vec3(posX, posY, posZ);
        this->WorldUp = glm::vec3(upX, upY, upZ);
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }

    // returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    }

    // processes input received from any keyboard-like input system.
    // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
    {
        GLfloat velocity = this->MovementSpeed * deltaTime;
        if (direction == FORWARD) {
            this->Position += this->Front * velocity;
        }
        if (direction == BACKWARD) {
            this->Position -= this->Front * velocity;
        }
        if (direction == LEFT) {
            this->Position -= this->Right * velocity;
        }
        if (direction == RIGHT) {
            this->Position += this->Right * velocity;
        }
    }

    // Processes input received from a mouse input system.
    //  Excepts the offset value in both the x-and-y direction.
    void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch/* = true*/)
    {
        xoffset *= this->MouseSensitivity;
        yoffset *= this->MouseSensitivity;

        this->Yaw += yoffset;
        this->Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get filled
        if (constrainPitch) {
            if (this->Pitch > 89.0f) {
                this->Pitch = 89.0f;
            }
            if (this->Pitch < -89.0f) {
                this->Pitch = -89.0f;
            }
        }

        // Update front, right and up vectors using the updated Eular angles
        this->updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event.
    //   only requires input on the vertical wheel-axis
    void Camera::ProcessMouseScroll(GLfloat yoffset)
    {
        if (this->Zoom >= 1.0f && this->Zoom <= 45.0f) {
            this->Zoom -= yoffset;
        }
        if (this->Zoom <= 1.0f) {
            this->Zoom = 1.0f;
        }
        if (this->Zoom >= 45.0f) {
            this->Zoom = 45.0f;
        }
    }

    // calculates the front vector from the camera's updated Eular Angles
    void Camera::updateCameraVectors()
    {
        // calcuate the new Front vect
        glm::vec3 front;
        front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
        front.y = sin(glm::radians(this->Pitch));
        front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
        this->Front = glm::normalize(front);

        // also re-calculate the right and up vector...
        // normalize the vectors, coz their length gets closer to 0 the more you look up or down which results in slower movement.
        this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
        this->Up = glm::normalize(glm::cross(this->Right, this->Front));
    }
