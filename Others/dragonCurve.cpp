
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <cmath>

#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265358979

struct Point {
    double x, y;
};

// Function to generate the Dragon Curve points
std::vector<Point> generateDragonCurve(int depth) {
    std::vector<Point> points;
    points.push_back({WIDTH / 4.0, HEIGHT / 2.0});
    points.push_back({WIDTH / 2.0, HEIGHT / 4.0});
    points.push_back({WIDTH * 3.0 / 4.0, HEIGHT / 2.0});
    
    double length = sqrt((WIDTH * WIDTH / 16.0) + (HEIGHT * HEIGHT / 16.0));

    // Iteratively generate points for the Dragon Curve
    for (int d = 0; d < depth; d++) {
        length /= sqrt(2.0);
        std::vector<Point> newPoints;
        for (int i = 0; i < points.size() - 1; i++) {
            double x1 = points[i].x;
            double y1 = points[i].y;
            double x2 = points[i + 1].x;
            double y2 = points[i + 1].y;
            
            double theta = atan2(y2 - y1, x2 - x1);
            double len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) / sqrt(2.0);
            double deltaAngle = ((i % 2) == 0) ? (PI / 4.0) : -(PI / 4.0);
            double newX = x1 + len * cos(theta + deltaAngle);
            double newY = y1 + len * sin(theta + deltaAngle);
            
            newPoints.push_back(points[i]);
            newPoints.push_back({newX, newY});
        }
        newPoints.push_back(points[points.size() - 1]);
        points = newPoints;
    }

    return points;
}

// Function to draw the Dragon Curve
void drawDragonCurve(int depth) {
    std::vector<Point> points = generateDragonCurve(depth);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);  // Set line color to green
    
    glBegin(GL_LINES);
    for (const auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dragon Curve Fractal", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);  // Set orthographic projection
    glMatrixMode(GL_MODELVIEW);

    int max_depth = 12;  // Set the initial depth for the Dragon Curve

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Draw the Dragon Curve with the current depth
        drawDragonCurve(max_depth);
        
        // Handle key inputs for interaction
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            max_depth++;  // Increase the depth when the UP arrow is pressed
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            if (max_depth > 1) max_depth--;  // Decrease the depth when the DOWN arrow is pressed
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
