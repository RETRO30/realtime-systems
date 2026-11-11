cmake_minimum_required(VERSION 3.16)

project(realtime_systems LANGUAGES CXX)

find_package(Threads REQUIRED)

add_executable(lab3 main.cpp)
target_compile_features(lab3 PRIVATE cxx_std_20)
set_target_properties(lab3 PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(lab3 PRIVATE Threads::Threads)
