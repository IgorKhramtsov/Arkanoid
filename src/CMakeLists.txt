list(APPEND SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BrickGO.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BrickGO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PlatformGO.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PlatformGO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BallGO.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BallGO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyApp.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MyApp.cpp
)

set(SOURCES ${SOURCES} PARENT_SCOPE)