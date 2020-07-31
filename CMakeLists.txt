cmake_minimum_required(VERSION 3.0.0)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)

add_subdirectory(src/)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glew)
add_subdirectory(lib/glm)

add_executable(Arkanoid ${SOURCES})

# find_package(OpenGL REQUIRED) 

target_link_libraries(Arkanoid
    glfw
    libglew_static
    glm
)