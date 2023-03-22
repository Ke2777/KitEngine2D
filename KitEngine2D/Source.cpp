#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <entt/entt.hpp>
#include "Sprite.h"
#include "InputManager.h"
#include "Components.h"
#include "ShaderSystem.h"
#include "RenderSystem.h"
#include "SpriteSystem.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) 
    {
        glViewport(0, 0, width, height);
    });

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    //auto firstShader = std::make_shared<Shader>(".\\Resources\\Shaders\\Triangle_Vertex.glsl", ".\\Resources\\Shaders\\Triangle_Fragment.glsl");
    //Sprite firstSprite(".\\Resources\\Textures\\anime2.jpg");
    //firstSprite.SetShader(firstShader);

    InputManager &inputManager = InputManager::getInstance(window);

    entt::registry registry;

    auto entity = registry.create();
    registry.emplace<SpriteComponent>(entity, ".\\Resources\\Textures\\anime2.jpg");
    registry.emplace<ShaderComponent>(entity, ".\\Resources\\Shaders\\Triangle_Vertex.glsl", ".\\Resources\\Shaders\\Triangle_Fragment.glsl");
    auto& transformComponent = registry.emplace<TransformComponent>(entity);

    ShaderSystem shaderSystem;
    shaderSystem.Update(registry, 1);
    SpriteSystem spriteSystem;
    spriteSystem.Update(registry, 1);    
    RenderSystem renderSystem;
  
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        inputManager.update();
        
        glClearColor(0,1,0,1);

        if (inputManager.IsKeyDown(KeyCode::A))
        {
            std::cout << "Pressed A";
        }        
        
        if (inputManager.IsMouseButtonPressed(MouseCode::MOUSE_BUTTON_4))
        {
            //std::cout << "Pressed Mouse 4";
            transformComponent.scale += 0.005f;
        }

        if (inputManager.IsMouseButtonPressed(MouseCode::MOUSE_BUTTON_5))
        {
            //std::cout << "Pressed Mouse 4";
            transformComponent.scale -= 0.005f;
        }

      // std::cout << inputManager.GetMousePosition().x << std::endl;
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
 //       firstSprite.Render();
        renderSystem.Update(registry, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}