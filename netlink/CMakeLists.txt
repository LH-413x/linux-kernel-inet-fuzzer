include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

set(srcs libnetlink.cpp)
add_library(netlink STATIC ${srcs})
#set_target_properties(netlink PROPERTIES OUTPUT_NAME "netlink")
