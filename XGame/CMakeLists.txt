
include("${China2D}/China2D.cmake")

include_directories(
    "${China2DApi}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Common"
    "${CMAKE_CURRENT_SOURCE_DIR}/Interface"
)


file(GLOB Common "${CMAKE_CURRENT_SOURCE_DIR}/Common/*.*")
file(GLOB Interface "${CMAKE_CURRENT_SOURCE_DIR}/Interface/*.*")

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/China2DTest)
