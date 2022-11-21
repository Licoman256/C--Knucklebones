#include <GLFW/glfw3.h>
#include "game.h"

int main(void) {

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    Game game;
    GLFWwindow* window = glfwCreateWindow(Field::WINDOW_WIDTH, Field::WINDOW_HEIGHT, "Knucklebones", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //tell opengl where to render
    glViewport(0, 0, Field::WINDOW_WIDTH, Field::WINDOW_HEIGHT);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        game.Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        //ui.HandleCommands();
        //game.Tick();
    }
    glfwTerminate();
    return 0;
}