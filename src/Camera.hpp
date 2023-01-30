#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// initial values
constexpr float INITIAL_YAW   = -90.0f;
constexpr float INITIAL_PITCH = 0.0f;
constexpr float SPEED         = 4.5f;
constexpr float SENSITIVITY   = 0.1f;

class Camera {
public:
    enum Direction { FRONT, BACK, RIGTH, LEFT, UP, DOWN };
    // Attributes
private:
    glm::vec3 m_position;
    glm::vec3 m_target;

    glm::vec3 m_direction;
    glm::vec3 m_rightAxis;
    glm::vec3 m_upAxis;

    float m_yaw;
    float m_pitch;

    float m_movementSpeed;
    float m_mouseSensitivity;

    // Member functions
public:
    Camera(const glm::vec3& position = glm::vec3 { 0.0f, 0.0f, 1.0f });

    ~Camera();
    void updateCoordinateSystem();
    void translate(Direction direction);
    void processMouseOffsets(float xoffset, float yoffset);
    glm::mat4x4 getViewMatrix();
};

#endif // __CAMERA_H__