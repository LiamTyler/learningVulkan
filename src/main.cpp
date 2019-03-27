#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <set>

const int SW = 800;
const int SH = 600;

#undef NDEBUG

#ifdef NDEBUG
const std::vector<const char*> validationLayers = {};
#else
const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};
#endif

bool checkValidationLayersPresent(const std::vector<const char*>& layers) {
    if (!layers.size())
        return true;

    // query for available layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    //std::cout << "Available validation layers:" << std::endl;
    //for (const auto& layerProperties : availableLayers) {
    //    std::cout << "\t" << layerProperties.layerName << std::endl;
    //}

    // check if all the desired validation layers are available
    for (const auto& layerName : layers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

bool createVkInstance(VkInstance& instance, const std::vector<const char*>& validationLayers) {
    if (!checkValidationLayersPresent(validationLayers)) {
        std::cout << "One or more validation layer unavailable" << std::endl;
        return false;
    }
    // struct that holds info about our application. Optional, but can help driver optimize sometimes
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // non-optional struct that specifies which global extension and validation layers to use
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Vulkan by itself doesn't know how to any platform things, so we do need extensions.
    // Specifically, we at least need the ones to interface with the windowing API, so ask
    // glfw for the extensions needed for this. Also the debug utils layer to print out layer messages
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensionNames(glfwExtensions, glfwExtensions + glfwExtensionCount);
    extensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());
    createInfo.ppEnabledExtensionNames = extensionNames.data();
    std::cout << "extensions needed" << std::endl;
    for (size_t i = 0; i < extensionNames.size(); i++)
        std::cout << "\t" << extensionNames[i] << std::endl;

    // how many global validation layers
    if (validationLayers.size()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    // query, and then print the available extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:" << std::endl;
    for (const auto& extension : extensions) {
        std::cout << "\t" << extension.extensionName << std::endl;
    }

    return vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    //if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    //    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    //}
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

// Attempts to create the debug message, if the extension function is found. True on sucess, false otherwise
bool CreateDebugUtilsMessengerEXT(const VkInstance& instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger) == VK_SUCCESS;
    }
    else {
        return false;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

bool createDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT& messenger) {
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    // | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT; // general verbose debug info
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData = nullptr; // Optional

    return CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &messenger);
}

struct QueueFamilyIndices {
    uint32_t graphicsFamily = -1;
    uint32_t presentFamily = -1;

    bool isComplete() {
        return graphicsFamily != -1 && presentFamily != -1;
    }
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (queueFamily.queueCount > 0 && presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    return findQueueFamilies(device, surface).isComplete();
}

bool pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface, VkPhysicalDevice& physicalDevice) {
    physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0)
        return false;

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device, surface)) {
            physicalDevice = device;
            break;
        }
    }

    return physicalDevice != VK_NULL_HANDLE;
}

bool createLogicalDevice(VkInstance instance, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, const std::vector<const char*>& validationLayers,
    VkDevice& device, VkQueue& graphicsQueue, VkQueue& presentQueue)
{
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);

    VkPhysicalDeviceFeatures deviceFeatures = {};
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

    if (validationLayers.size()) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
        return false;

    vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);

    return true;
}

bool createSurface(VkInstance instance, GLFWwindow* window, VkSurfaceKHR& surface) {
    return glfwCreateWindowSurface(instance, window, nullptr, &surface) == VK_SUCCESS;
}

int main() {
    glfwInit();

    // tell glfw not to create an opengl context (like it normally does)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(SW, SH, "Vulkan window", nullptr, nullptr);

    VkInstance vkInstance;
    if (!createVkInstance(vkInstance, validationLayers)) {
        std::cout << "Could not create the vulkan instance" << std::endl;
        return EXIT_FAILURE;
    }

    VkDebugUtilsMessengerEXT debugMessenger;
    if (!createDebugMessenger(vkInstance, debugMessenger)) {
        std::cout << "Could not create the vulkan debug messenger" << std::endl;
        return EXIT_FAILURE;
    }

    VkSurfaceKHR surface;
    if (!createSurface(vkInstance, window, surface)) {
        std::cout << "Could not create the surface" << std::endl;
        return EXIT_FAILURE;
    }

    // physical device implicitly destoryed with the instance
    VkPhysicalDevice physicalDevice;
    if (!pickPhysicalDevice(vkInstance, surface, physicalDevice)) {
        std::cout << "No suitable physical devices to use" << std::endl;
        return EXIT_FAILURE;
    }

    VkDevice logicalDevice;
    VkQueue graphicsQueue, presentQueue;
    if (!createLogicalDevice(vkInstance, physicalDevice, surface, validationLayers, logicalDevice, graphicsQueue, presentQueue)) {
        std::cout << "Failed to create logical device" << std::endl;
        return EXIT_FAILURE;
    }



    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    // cleanup
    vkDestroyDevice(logicalDevice, nullptr);
    vkDestroySurfaceKHR(vkInstance, surface, nullptr);
    DestroyDebugUtilsMessengerEXT(vkInstance, debugMessenger, nullptr);
    vkDestroyInstance(vkInstance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
