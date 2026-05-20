cmake_minimum_required(VERSION 3.22.1)

project(native_image_processor LANGUAGES CXX)

add_library(
    native_image_processor
    SHARED
    native-lib.cpp
    core/image_processor.cpp
)

target_compile_features(native_image_processor PRIVATE cxx_std_17)

target_include_directories(
    native_image_processor
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)

find_library(log-lib log)

target_link_libraries(
    native_image_processor
    ${log-lib}
)
