
find_package(Boost REQUIRED CONFIG COMPONENTS
    container
    describe
    geometry
    graph
    multi_index
    stacktrace_addr2line
    static_string
    type_traits
    uuid
    program_options
)

find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenXR CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
