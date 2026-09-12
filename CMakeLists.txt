cmake_minimum_required(VERSION 3.10.0)
project(ARUI VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "/usr/bin/clang")
include(cmake/FindDeps.cmake)
#include(cmake/FetchLLVM.cmake)
enable_testing()
include(cmake/CompileShaders.cmake)

add_spirv_shader_library(
    TARGET
        ARUI_OpenGLShaders

    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/Server/res/Shaders/OpenGL"

    TARGET_ENV
        opengl

    NAMESPACE
        ARUI::Shaders::OpenGL
)

file(GLOB_RECURSE ARUI_SERVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Server/src/**.cpp")

add_executable(AruiServer ${ARUI_SERVER_SOURCES})
target_link_libraries(AruiServer PRIVATE
    ARUI_OpenGLShaders

    Boost::container
    Boost::describe
    Boost::geometry
    Boost::graph
    Boost::multi_index
    Boost::stacktrace_addr2line
    Boost::static_string
    Boost::type_traits
    Boost::uuid
    Boost::program_options
    Boost::lockfree
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    imgui::imgui
    implot::implot
    glfw
    GLEW::GLEW
    glm::glm
    OpenXR::headers OpenXR::openxr_loader
    fg::FrameGraph
    Vulkan::Vulkan
    GPUOpen::VulkanMemoryAllocator
    bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode #For compatability
)
target_include_directories(AruiServer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Server/include")
