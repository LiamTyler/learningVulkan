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
    bool createImageViews();
    bool createRenderPass();
    bool createGraphicsPipeline();
    bool createFramebuffers();
    bool createCommandPool();
    bool createCommandBuffers();


    // TODO: make private
    extern GLFWwindow* window;
    extern int SW, SH;
    extern VkInstance instance;
    extern VkDebugUtilsMessengerEXT debugMessenger;
    extern VkSurfaceKHR surface;
    extern VkPhysicalDevice physicalDevice;
    extern VkDevice logicalDevice;
    extern VkQueue graphicsQueue, presentQueue;
    extern VkSwapchainKHR swapChain;
    extern std::vector<VkImage> swapChainImages;
    extern VkFormat swapChainImageFormat;
    extern VkExtent2D swapChainExtent;
    extern std::vector<VkImageView> swapChainImageViews;
    extern VkRenderPass renderPass;
    extern VkPipelineLayout pipelineLayout;
    extern VkPipeline graphicsPipeline;
    extern std::vector<VkFramebuffer> swapChainFramebuffers;
    extern VkCommandPool commandPool;
    extern std::vector<VkCommandBuffer> commandBuffers;

} // namespace graphics

