
# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("${CMAKE_CURRENT_SOURCE_DIR}/../China2D.cmake")
find_package(OpenGL REQUIRED)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Graphics/OpenGL/Glfw)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/OpenGL/Glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/OpenGL/Glfw/include
    ${OPENGL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/Components/Interface
)

file(GLOB libGlew "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/OpenGL/Glew/lib/*.lib")


file(GLOB Interface "${CMAKE_CURRENT_SOURCE_DIR}/Interface/*.*")
file(GLOB Components "${CMAKE_CURRENT_SOURCE_DIR}/Components/*.*")
file(GLOB ComponentsInterface "${CMAKE_CURRENT_SOURCE_DIR}/Components/Interface/*.*")
file(GLOB Log "${CMAKE_CURRENT_SOURCE_DIR}/Components/Log/*.*")
file(GLOB Logic "${CMAKE_CURRENT_SOURCE_DIR}/Components/Logic/*.*")
file(GLOB ResourceManager "${CMAKE_CURRENT_SOURCE_DIR}/Components/ResourceManager/*.*")
file(GLOB TaskManager "${CMAKE_CURRENT_SOURCE_DIR}/Components/TaskManager/*.*")


file(GLOB Graphics "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.*")

source_group(Interface FILES ${Interface})
source_group(Components FILES ${Components})
source_group(Components\\Interface FILES ${ComponentsInterface})
source_group(Components\\Log FILES ${Log})
source_group(Components\\Logic FILES ${Logic})
source_group(Components\\ResourceManager FILES ${ResourceManager})
source_group(Components\\TaskManager FILES ${TaskManager})
source_group(Graphics FILES ${Graphics})
source_group(\\ FILES main.cpp Engine.h Engine.cpp)

add_executable(China2D
    ${China2DApi}
    ${Interface}
    ${Components}
    ${ComponentsInterface}
    ${Log}
    ${Logic}
    ${ResourceManager}
    ${TaskManager}
    ${Graphics}
    ${Utils}
    Engine.h
    Engine.cpp
    main.cpp
)

target_link_libraries(China2D PRIVATE
    ${OPENGL_LIBRARIES}
    ${libGlew}
    glfw
)
