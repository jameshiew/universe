#include <GLFW/glfw3.h>

#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    if (!glfwInit())
    {
        // Initialization failed
    }
    glfwTerminate();
    return 0;
}