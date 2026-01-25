#cmake file for project core
#author : {auther}
#created : {date}

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

file(GLOB China2DTest "*.*")

include("${China2D}/China2D.cmake")

source_group(Interface FILES ${Interface})
source_group(Common FILES ${Common})
source_group(\\ FILES ${China2DTest})

add_library (China2DTest SHARED
    ${China2DApi}
    ${Common}
    ${Interface}
    ${Utils}
    ${China2DTest}
)

set_property(TARGET China2DTest PROPERTY FOLDER "Test")
