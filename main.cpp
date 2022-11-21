#include <GLFW/glfw3.h>
#include "game.h"

int main(void) {

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    Game game;
    GLFWwindow* window = glfwCreateWindow(game.WINDOW_WIDTH, game.WINDOW_HEIGHT, "Knucklebones", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //tell opengl where to render
    glViewport(0, 0, game.WINDOW_WIDTH, game.WINDOW_HEIGHT);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        //game.Render();
        //game.Tick();
        //ui.HandleCommands();
        game.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}