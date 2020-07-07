cmake_minimum_required(VERSION 3.1)
project(muscle_lib
    VERSION 1.0.0
    DESCRIPTION "muscle lib"
    LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall -I/usr/local/include -L/usr/local/lib -lwiringPi")

file(GLOB SOURCE_FILES "src/*.cxx" "src/*.cpp" "src/*.c")
set(SOURCE ${SOURCE_FILES})
add_library(muscle STATIC ${SOURCE})

target_compile_features(muscle PRIVATE cxx_std_11) #ビルドプロパティの指定
target_include_directories(muscle INTERFACE ./inc)
set_target_properties(muscle
    PROPERTIES
    VERSION ${PROJECT_VERSION})