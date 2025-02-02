
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

double centerX = -0.5, centerY = 0.0, zoom = 1.0;
const int max_iter = 100;

// Mandelbrot computation function
void drawMandelbrot() {
    glBegin(GL_POINTS);
    for (int px = 0; px < 800; px++) {
        for (int py = 0; py < 800; py++) {
            float x0 = centerX + (px / 800.0f - 0.5f) * 3.5f / zoom;
            float y0 = centerY + (py / 800.0f - 0.5f) * 2.0f / zoom;
            float x = 0.0f, y = 0.0f;
            int iter = 0;

            while (x*x + y*y < 4.0f && iter < max_iter) {
                float xtemp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xtemp;
                iter++;
            }

            float color = (float) iter / max_iter;
            glColor3f(color, color * 0.5f, 1.0f - color);
            glVertex2f((px / 400.0f) - 1.0f, (py / 400.0f) - 1.0f);
        }
    }
    glEnd();
}

// Keyboard controls for zooming and panning
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        double zoomSpeed = 1.1;
        double moveSpeed = 0.1 / zoom;

        if (key == GLFW_KEY_Z) zoom *= zoomSpeed;      // Zoom in
        if (key == GLFW_KEY_X) zoom /= zoomSpeed;      // Zoom out
        if (key == GLFW_KEY_W) centerY += moveSpeed;   // Move up
        if (key == GLFW_KEY_S) centerY -= moveSpeed;   // Move down
        if (key == GLFW_KEY_A) centerX -= moveSpeed;   // Move left
        if (key == GLFW_KEY_D) centerX += moveSpeed;   // Move right
    }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 800, "Mandelbrot (CPU)", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawMandelbrot();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
