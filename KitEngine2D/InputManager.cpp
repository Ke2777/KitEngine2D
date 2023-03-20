#include "InputManager.h"

InputManager& InputManager::getInstance(GLFWwindow* window) {
    static InputManager instance(window);
    return instance;
}

void InputManager::update() {
    glfwPollEvents();
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    mousePosition = glm::vec2((float)xPos, (float)yPos);
}

bool InputManager::IsKeyDown(KeyCode key) {
    int state = glfwGetKey(window, static_cast<int>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool InputManager::IsKeyUp(KeyCode key) {
    int state = glfwGetKey(window, static_cast<int>(key));
    return state == GLFW_RELEASE;
}

bool InputManager::IsMouseButtonPressed(MouseCode button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool InputManager::IsMouseButtonReleased(MouseCode button) {
    return glfwGetMouseButton(window, button) == GLFW_RELEASE;
}

bool InputManager::IsMouseButtonHeld(MouseCode button) {
    return glfwGetMouseButton(window, button) == GLFW_REPEAT;
}

const glm::vec2& InputManager::GetMousePosition() {
    return mousePosition;
}

InputManager::InputManager(GLFWwindow* window) {
    this->window = window;
    mousePosition = glm::vec2(0, 0);
}