cmake_minimum_required(VERSION 3.16)

project(RouterNetworkSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Every time you write a new class, add its .h and .cpp here
add_executable(router_network
    src/main.cpp
    src/router.h src/router.cpp
    src/network.h src/network.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(router_network PRIVATE -Wall -Wextra -Wpedantic)
endif()
