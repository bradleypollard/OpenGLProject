#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Quit if the user hits escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

	// Initialise GLFW. If it fails, quit.
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
	}

	// Create a window. If it fails, exit.
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	// Set the current window to be the window we created (can have multiple).
    glfwMakeContextCurrent(window);
	// Set the callback for keys getting hit for this window.
    glfwSetKeyCallback(window, key_callback);

	// Main loop
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

		// Get the framebuffer size for glViewport and glOrtho.
		// Alternately use framebuffer_size_callback().
        glfwGetFramebufferSize(window, &width, &height);
		// Aspect ratio, to use in Ortho to transform image to display with perspective?
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

		// Projection - Perspective?
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		// Model View -> World View -> Camera View -> Projection
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
		// Rotate using the timer glfwGetTime().
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		// Draw a triangle from some points, much like GLUT.
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();

		// Swap the front and back buffers.
        glfwSwapBuffers(window);
		// Communicate with window system to receive events. Done before rendering, but after buffer swap.
		// PollEvents(), good for rendering continually like games. WaitEvents() good for rendering when getting new input.
        glfwPollEvents();
    }

	// If we fall out the loop, destroy the window, and exit.
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
