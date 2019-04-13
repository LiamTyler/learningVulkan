#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <vector>
#include <array>

namespace graphics {

    bool initVulkan(int screenWidth, int screenHeight);
    void cleanup();

    bool drawFrame();

    bool createInstance();
    bool setupDebugCallback();
    bool createSurface();
    bool pickPhysicalDevice();
    bool createLogicalDevice();
    bool createSwapChain();
    bool createImageViews();
    bool createRenderPass();
    bool createDescriptorSetLayout();
    bool createGraphicsPipeline();
    bool createFramebuffers();
    bool createCommandPool();
    bool createVertexBuffer();
    bool createIndexBuffer();
    bool createUniformBuffers();
    bool createCommandBuffers();
    bool createSyncObjects();
    void cleanupSwapChain();
    void recreateSwapChain();


    struct QueueFamilyIndices {
        uint32_t graphicsFamily = -1;
        uint32_t presentFamily = -1;

        bool isComplete() const {
            return graphicsFamily != -1 && presentFamily != -1;
        }
    };

    struct PhysicalDeviceInfo {
        VkPhysicalDevice device;
        int score;
        QueueFamilyIndices indices;
    };

    // TODO: make private
    extern GLFWwindow* window;
    extern int SW, SH;
    extern VkInstance instance;
    extern VkDebugUtilsMessengerEXT debugMessenger;
    extern VkSurfaceKHR surface;
    extern PhysicalDeviceInfo physicalDeviceInfo;
    extern VkDevice logicalDevice;
    extern VkQueue graphicsQueue, presentQueue;
    extern VkSwapchainKHR swapChain;
    extern std::vector<VkImage> swapChainImages;
    extern VkFormat swapChainImageFormat;
    extern VkExtent2D swapChainExtent;
    extern std::vector<VkImageView> swapChainImageViews;
    extern VkRenderPass renderPass;
    extern VkDescriptorSetLayout descriptorSetLayout;
    extern VkPipelineLayout pipelineLayout;
    extern VkPipeline graphicsPipeline;
    extern std::vector<VkFramebuffer> swapChainFramebuffers;
    extern VkCommandPool commandPool;
    extern std::vector<VkCommandBuffer> commandBuffers;
    extern std::vector<VkSemaphore> imageAvailableSemaphores;
    extern std::vector<VkSemaphore> renderFinishedSemaphores;
    extern std::vector<VkFence> inFlightFences;
    extern size_t currentFrame;
    extern bool framebufferResized;
    extern VkBuffer vertexBuffer;
    extern VkDeviceMemory vertexBufferMemory;
    extern VkBuffer indexBuffer;
    extern VkDeviceMemory indexBufferMemory;
    extern std::vector<VkBuffer> uniformBuffers;
    extern std::vector<VkDeviceMemory> uniformBuffersMemory;


} // namespace graphics

