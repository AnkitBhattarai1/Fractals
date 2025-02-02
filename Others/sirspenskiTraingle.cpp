
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

int depth = 5;  // Recursion depth

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawSierpinski(float x1, float y1, float x2, float y2, float x3, float y3, int level) {
    if (level == 0) {
        drawTriangle(x1, y1, x2, y2, x3, y3);
        return;
    }

    float mid1x = (x1 + x2) / 2, mid1y = (y1 + y2) / 2;
    float mid2x = (x2 + x3) / 2, mid2y = (y2 + y3) / 2;
    float mid3x = (x3 + x1) / 2, mid3y = (y3 + y1) / 2;

    drawSierpinski(x1, y1, mid1x, mid1y, mid3x, mid3y, level - 1);
    drawSierpinski(mid1x, mid1y, x2, y2, mid2x, mid2y, level - 1);
    drawSierpinski(mid3x, mid3y, mid2x, mid2y, x3, y3, level - 1);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    drawSierpinski(-0.7f, -0.5f, 0.7f, -0.5f, 0.0f, 0.6f, depth);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_UP) depth++;       // Increase recursion depth
        if (key == GLFW_KEY_DOWN) depth = std::max(1, depth - 1); // Decrease depth
    }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 800, "Sierpiński Triangle", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
