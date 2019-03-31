cmake_minimum_required (VERSION 3.0)

project(Vulkan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Disable building extras we won't need (pure C++ project)
set(GLFW_BUILD_EXAMPLES  OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_TESTS     OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_DOCS      OFF CACHE BOOL " " FORCE)

add_subdirectory(ext/glfw)


set(
    SRCS
    src/main.cpp
    src/graphics_api.cpp
)

set(
    HEADERS
    include/graphics_api.hpp
)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

if (MSVC)
    set(INCLUDE_DIRS
        C:/VulkanSDK/1.1.101.0/Include
        ${INCLUDE_DIRS}
    )
endif()

set(SYSTEM_LIBS "")
if (UNIX AND NOT APPLE)
    set(SYSTEM_LIBS
        dl
        stdc++fs
    )
endif()

set(LIBS
    glfw
    vulkan-1
    ${SYSTEM_LIBS}
)

if (UNIX)
    set(LIB_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}/lib
    )

    find_package(Vulkan REQUIRED)
    #target_link_libraries(vulkaninfo Vulkan::Vulkan)
    set(LIBS
        glfw
        Vulkan::Vulkan
        ${SYSTEM_LIBS}
    )
else()
    set(LIB_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}/lib
        C:/VulkanSDK/1.1.101.0/Lib
    )
    set(LIBS
        glfw
        vulkan-1
        ${SYSTEM_LIBS}
    )
endif()

link_directories(${LIB_DIRS})
include_directories(${INCLUDE_DIRS})

add_executable(app ${SRCS} ${HEADERS})
target_link_libraries(app ${LIBS})
