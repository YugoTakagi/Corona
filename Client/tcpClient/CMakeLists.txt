cmake_minimum_required(VERSION 3.1)
project(tcpClient_lib
    VERSION 1.0.0
    DESCRIPTION "tcpClient lib"
    LANGUAGES CXX)

file(GLOB SOURCE_FILES "src/*.cxx" "src/*.cpp" "src/*.c")
set(SOURCE ${SOURCE_FILES})
add_library(tcpClient STATIC ${SOURCE})

target_compile_features(tcpClient PRIVATE cxx_std_11) #ビルドプロパティの指定
target_include_directories(tcpClient INTERFACE ./inc)
set_target_properties(tcpClient
    PROPERTIES
    VERSION ${PROJECT_VERSION})