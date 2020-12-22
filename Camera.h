#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const glm::vec3 vec3_zero(0, 0, 0);
const glm::vec3 vec3_y_dir(0, 1, 0);
const glm::vec3 vec3_z_dir(0, 0, 1);
class Camera
{
public:
    Camera(glm::vec3 pos = vec3_zero,glm::vec3 up = vec3_y_dir,float yaw = -90,float pitch = 0);
    ~Camera();

    void Update();

    glm::mat4 GetVieMatrix();

    float GetZoom();
    void  SetZoom(float zoom);

    void SetMousePos(double x, double y, bool isFirst = false,bool constrainPitch = true);

    void MoveCamera(Camera_Movement direction);
    void SetFPS(float fps);

    glm::vec3 GetPosition();
private:

    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed = 2.5;
    float MouseSensitivity = 0.1;
    float Zoom = 45;

    double LastMouseX;
    double LastMouseY;
    bool   firstMouse;
    double Fps = 0.0;
    
    
};