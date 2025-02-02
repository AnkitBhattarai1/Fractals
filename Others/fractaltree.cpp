
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

int depth = 7;  // Recursion depth
float branchAngle = 30.0f; // Angle between branches

void drawBranch(float length, int level) {
    if (level == 0) return;

    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, length);
    glEnd();

    glTranslatef(0, length, 0);

    glPushMatrix();
    glRotatef(branchAngle, 0, 0, 1);
    drawBranch(length * 0.7f, level - 1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-branchAngle, 0, 0, 1);
    drawBranch(length * 0.7f, level - 1);
    glPopMatrix();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, -1.0f, 0);
    drawBranch(0.3f, depth);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_UP) depth++;       // Increase recursion depth
        if (key == GLFW_KEY_DOWN) depth = std::max(1, depth - 1); // Decrease depth
        if (key == GLFW_KEY_LEFT) branchAngle -= 5.0f; // Decrease branch angle
        if (key == GLFW_KEY_RIGHT) branchAngle += 5.0f; // Increase branch angle
    }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 800, "Fractal Tree", NULL, NULL);
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
