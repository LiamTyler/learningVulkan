#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <vector>

namespace graphics {

    bool initVulkan(int screenWidth, int screenHeight);
    void cleanup();

    bool createInstance();
    bool setupDebugCallback();
    bool createSurface();
    bool pickPhysicalDevice();
    bool createLogicalDevice();
    bool createSwapChain();

    extern GLFWwindow* window;
    extern int SW, SH;
    extern VkInstance instance;
    extern VkDebugUtilsMessengerEXT debugMessenger;
    extern VkSurfaceKHR surface;
    extern VkPhysicalDevice physicalDevice;
    extern VkDevice logicalDevice;
    extern VkQueue graphicsQueue, presentQueue;
    extern VkSwapchainKHR swapChain;

} // namespace graphics

