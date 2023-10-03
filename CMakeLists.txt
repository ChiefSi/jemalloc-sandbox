cmake_minimum_required(VERSION 3.0.2)

project(jemalloc-sandbox)

find_package(PkgConfig REQUIRED)
pkg_check_modules(jemalloc REQUIRED IMPORTED_TARGET jemalloc)

find_package(Threads)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Threads::Threads PkgConfig::jemalloc)
