#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum KeyCode {
    // Цифровые клавиши
    KEY_0 = GLFW_KEY_0,
    KEY_1 = GLFW_KEY_1,
    KEY_2 = GLFW_KEY_2,
    KEY_3 = GLFW_KEY_3,
    KEY_4 = GLFW_KEY_4,
    KEY_5 = GLFW_KEY_5,
    KEY_6 = GLFW_KEY_6,
    KEY_7 = GLFW_KEY_7,
    KEY_8 = GLFW_KEY_8,
    KEY_9 = GLFW_KEY_9,

    // Буквенные клавиши
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,

    // Функциональные клавиши
    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,

    // Другие клавиши
    SPACE = GLFW_KEY_SPACE,
    ENTER = GLFW_KEY_ENTER,
    ESCAPE = GLFW_KEY_ESCAPE,
    TAB = GLFW_KEY_TAB,
    BACKSPACE = GLFW_KEY_BACKSPACE,
    CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
    LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
    RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
    LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
    RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
    LEFT_ALT = GLFW_KEY_LEFT_ALT,
    RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
    LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
    RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
    MENU = GLFW_KEY_MENU,
};

enum MouseCode {
    MOUSE_BUTTON_1 = 0,
    MOUSE_BUTTON_2 = 1,
    MOUSE_BUTTON_3 = 2,
    MOUSE_BUTTON_4 = 3,
    MOUSE_BUTTON_5 = 4,
    MOUSE_BUTTON_6 = 5,
    MOUSE_BUTTON_7 = 6,
    MOUSE_BUTTON_8 = 7,
    MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1,
    MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2,
    MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
};

class InputManager {
public:
    static InputManager& getInstance(GLFWwindow* window);

    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;

    void update();

    bool IsKeyDown(KeyCode key);
    bool IsKeyUp(KeyCode key);

    bool IsMouseButtonPressed(MouseCode button);
    bool IsMouseButtonReleased(MouseCode button);
    bool IsMouseButtonHeld(MouseCode button);

    const glm::vec2& GetMousePosition();

private:
    InputManager(GLFWwindow* window);

    GLFWwindow* window;
    glm::vec2 mousePosition;
};