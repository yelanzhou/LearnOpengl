#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    :Position(pos)
    ,WorldUp(up)
    ,Yaw(yaw)
    ,Pitch(pitch)
{
    Update();
}

Camera::~Camera()
{
}



glm::mat4 Camera::GetVieMatrix()
{
    return glm::lookAt(Position, Position + Front, WorldUp);
}

float Camera::GetZoom()
{
    return Zoom;
}

void Camera::SetZoom(float zoom)
{
    if (zoom < 1)
    {
        zoom = 1;
    }
    if (zoom > 45)
    {
        zoom = 45;
    }
    Zoom = zoom;
}

void Camera::SetMousePos(double x, double y, bool isFirst, bool constrainPitch)
{
    if (isFirst)
    {
        LastMouseX = x;
        LastMouseY = y;
        return;
    }

    float xoffset = x - LastMouseX;
    float yoffset = LastMouseY - y; // reversed since y-coordinates go from bottom to top

    LastMouseX = x;
    LastMouseY = y;

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    Update();


}

void Camera::MoveCamera(Camera_Movement direction)
{
    if (Fps == 0)
    {
        return;
    }
    float delta = 1 / Fps;
    float velocity = MovementSpeed * delta;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::SetFPS(float fps)
{
   
    Fps = fps;
}

glm::vec3 Camera::GetPosition()
{
    return Position;
}

void Camera::Update()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
