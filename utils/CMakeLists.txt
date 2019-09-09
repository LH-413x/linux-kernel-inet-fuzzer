include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

set(srcs utils.cpp)
add_library(util ${srcs})