#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Sprite.h"


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

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    auto firstShader = std::make_shared<Shader>(".\\Resources\\Shaders\\Triangle_Vertex.glsl", ".\\Resources\\Shaders\\Triangle_Fragment.glsl");
    Sprite firstSprite(".\\Resources\\Textures\\anime2.jpg");
    firstSprite.SetShader(firstShader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0,1,0,1);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        firstSprite.Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}