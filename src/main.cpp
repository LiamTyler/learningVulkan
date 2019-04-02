#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "graphics_api.hpp"

int main() {

    if (!graphics::initVulkan(800, 600))
        return EXIT_FAILURE;

    while(!glfwWindowShouldClose(graphics::window)) {
        glfwPollEvents();
        if (glfwGetKey(graphics::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(graphics::window, true);

        graphics::drawFrame();
    }

    graphics::cleanup();


    return 0;
}
