message(STATUS "China2D ${China2D}")

file(GLOB China2DApi "${China2D}/China2DApi/*.*")

include_directories(
    "${China2D}/China2DApi"
)

source_group(China2DApi FILES ${China2DApi})
