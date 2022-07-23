/* file name: glfwx64Source.cpp
 * create date: 2022-07-22-Fri
 * test under OpenGL libraries, such as GLFW. the program shows a window with a sentence.
 */

#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello, Window.", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/* file name: glfwx64Source.cpp
 * create date: 2022-07-22-Fri
 * test under OpenGL libraries, such as GLFW. the program shows a window with a sentence.
 * show a window titled 'Hello, Window.', means success!
 */