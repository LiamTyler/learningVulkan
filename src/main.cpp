#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <string>
#include <iostream>

const int SW = 800;
const int SH = 600;

int main() {
    glfwInit();

    // tell glfw not to create an opengl context (like it normally does)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(SW, SH, "Vulkan window", nullptr, nullptr);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
