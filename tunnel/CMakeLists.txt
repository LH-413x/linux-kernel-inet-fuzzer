include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

set(srcs tunnel.cpp)
link_directories(${CMAKE_BINARY_DIR}/lib)

add_library(tunnel ${srcs})
target_link_libraries(tunnel libutil.a)

add_executable(tunnel_test test_tunnel.cpp)
target_link_libraries(tunnel_test tunnel)

#${CMAKE_BINARY_DIR}/lib/