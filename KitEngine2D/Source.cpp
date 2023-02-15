#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Texture2D.h"
#include "Shader.h"


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

    float triangle[] = 
    {
      0.5f, 0.5f, 1.0f, 1.0f,        
      0.5f, -0.5f, 1.0f, 0.0f,
     -0.5f, -0.5f, 0.0f, 0.0f,
     -0.5f, 0.5f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
    0, 1, 3, // First triangle
    1, 2, 3  // Second triangle
    };



    GLuint VBO;
    GLuint EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Index array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    Shader triangleShader(".\\Resources\\Shaders\\Triangle_Vertex.glsl", ".\\Resources\\Shaders\\Triangle_Fragment.glsl");


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    // Creating Texture
    
    Texture2D texture(".\\Resources\\Textures\\anime2.jpg");
    texture.Bind();
    
    triangleShader.Bind();    
    triangleShader.SetInt("tex", 0);

    srand(time(NULL));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0,1,0,1);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        float r = (float)rand() / (float)(RAND_MAX / 1);
        float g = (float)rand() / (float)(RAND_MAX / 1);
        float b = (float)rand() / (float)(RAND_MAX / 1);
        float a = 1;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}