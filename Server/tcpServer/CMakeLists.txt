cmake_minimum_required(VERSION 3.1)
project(tcpServer_lib
    VERSION 1.0.0
    DESCRIPTION "tcpServer lib"
    LANGUAGES CXX)

file(GLOB SOURCE_FILES "src/*.cxx" "src/*.cpp" "src/*.c")
set(SOURCE ${SOURCE_FILES})
add_library(tcpServer STATIC ${SOURCE})

target_compile_features(tcpServer PRIVATE cxx_std_11) #ビルドプロパティの指定
target_include_directories(tcpServer INTERFACE ./inc)
set_target_properties(tcpServer
    PROPERTIES
    VERSION ${PROJECT_VERSION})