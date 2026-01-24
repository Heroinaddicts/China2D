message(STATUS "China2D ${China2D}")

file(GLOB China2DApi "${China2D}/China2DApi/*.*")
file(GLOB Utils "${China2D}/Utils/*.*")

include_directories(
    "${China2D}/China2DApi"
    "${China2D}/Utils"
)

source_group(China2DApi FILES ${China2DApi})
source_group(Utils FILES ${Utils})
