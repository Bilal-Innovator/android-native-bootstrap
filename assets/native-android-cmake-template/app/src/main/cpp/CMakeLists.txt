cmake_minimum_required(VERSION 3.22.1)

project(native_engine LANGUAGES CXX)

add_library(
    native_engine
    SHARED
    native-lib.cpp
    core/native_engine.cpp
)

target_compile_features(native_engine PRIVATE cxx_std_17)

target_include_directories(
    native_engine
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)

find_library(log-lib log)

target_link_libraries(
    native_engine
    ${log-lib}
)
