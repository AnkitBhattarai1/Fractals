
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <stack>

int depth = 6;  // Recursion depth
const float angle = 25.0f; // Angle between branches

struct State {
    float x, y, angle;
};

void drawBranch(float length) {
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, length);
    glEnd();
    glTranslatef(0, length, 0);
}

void drawFractalPlant(int level, float length) {
    if (level == 0) return;

    std::stack<State> stateStack;

    std::string axiom = "X";
    std::string rulesX = "F+[[X]-X]-F[-FX]+X"; // X expands into branches
    std::string rulesF = "FF"; // F moves forward

    std::string result = axiom;
    for (int i = 0; i < level; i++) {
        std::string nextResult;
        for (char c : result) {
            if (c == 'X') nextResult += rulesX;
            else if (c == 'F') nextResult += rulesF;
            else nextResult += c;
        }
        result = nextResult;
    }

    for (char c : result) {
        if (c == 'F') {
            drawBranch(length);
        } else if (c == '+') {
            glRotatef(angle, 0, 0, 1);
        } else if (c == '-') {
            glRotatef(-angle, 0, 0, 1);
        } else if (c == '[') {
            stateStack.push({0, 0, 0});
            glPushMatrix();
        } else if (c == ']') {
            glPopMatrix();
            stateStack.pop();
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_UP) depth++;        // Increase recursion depth
        if (key == GLFW_KEY_DOWN) depth = std::max(1, depth - 1); // Decrease depth
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, -1.0f, 0);
    drawFractalPlant(depth, 0.1f);
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 800, "Fractal Plant", NULL, NULL);
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
