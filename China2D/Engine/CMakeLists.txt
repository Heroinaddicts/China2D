
# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("${CMAKE_CURRENT_SOURCE_DIR}/../China2D.cmake")
find_package(OpenGL REQUIRED)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/Glfw)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/Glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/Glfw/include
    ${OPENGL_INCLUDE_DIR} # 显式包含OpenGL头文件路径，增强鲁棒性
)

file(GLOB libGlew "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/Glew/lib/*.lib")
source_group(\\ FILES main.cpp)

add_executable(China2D
    ${China2DApi}
    main.cpp
)

target_link_libraries(China2D PRIVATE
    ${OPENGL_LIBRARIES}
    ${libGlew}
    glfw
)

set_target_properties(China2D PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
)
