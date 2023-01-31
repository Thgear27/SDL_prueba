#include "Camera.hpp"
#include <iostream>

extern float deltaTime;

Camera::Camera(const glm::vec3& position) {
    m_position = position;
    m_target   = glm::vec3 { 0.0f, 0.0f, 0.0f };

    m_yaw              = INITIAL_YAW;
    m_pitch            = INITIAL_PITCH;
    m_movementSpeed    = INITIAL_SPEED;
    m_mouseSensitivity = INITIAL_SENSITIVITY;
    updateCoordinateSystem();
}

Camera::~Camera() {}

void Camera::updateCoordinateSystem() {
    glm::vec3 newFront;
    newFront.x  = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    newFront.y  = std::sin(glm::radians(m_pitch));
    newFront.z  = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    m_direction = glm::normalize(newFront);

    m_rightAxis = glm::normalize(glm::cross(m_direction, glm::vec3 { 0.0f, 1.0f, 0.0f }));
    m_upAxis    = glm::normalize(glm::cross(m_direction, m_rightAxis));
}

void Camera::translate(Direction direction) {
    glm::vec3 newFront = glm::normalize(glm::vec3 { m_direction.x, 0.0f, m_direction.z });
    if (direction == Direction::FRONT) m_position += (newFront * m_movementSpeed * deltaTime);
    if (direction == Direction::BACK) m_position -= (newFront * m_movementSpeed * deltaTime);
    if (direction == Direction::RIGTH) m_position += (m_rightAxis * m_movementSpeed * deltaTime);
    if (direction == Direction::LEFT) m_position -= (m_rightAxis * m_movementSpeed * deltaTime);
    if (direction == Direction::UP) m_position += (glm::vec3 { 0.0f, 1.0f, 0.0f } * m_movementSpeed * deltaTime);
    if (direction == Direction::DOWN) m_position -= (glm::vec3 { 0.0f, 1.0f, 0.0f } * m_movementSpeed * deltaTime);
}

void Camera::processMouseOffsets(float xoffset, float yoffset) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
    updateCoordinateSystem();
}

void Camera::setSensitivity(float newSensitivity) { m_mouseSensitivity = newSensitivity; }

void Camera::setMovementSpeed(float newSpeed) { m_movementSpeed = newSpeed; }

void Camera::printPosition() {
    std::cout << "Position( " << "x: " << m_position.x << " y: " << m_position.y << " z: " << m_position.z << " )\n";
}

glm::mat4x4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + m_direction, glm::vec3 { 0.0f, 1.0f, 0.0f });
}
