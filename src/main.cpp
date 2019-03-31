#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "graphics_api.hpp"


int main() {

    graphics::initVulkan(800, 600);

    while(!glfwWindowShouldClose(graphics::window)) {
        glfwPollEvents();
        if (glfwGetKey(graphics::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(graphics::window, true);
    }

    graphics::cleanup();


    return 0;
}
