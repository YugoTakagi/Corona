cmake_minimum_required(VERSION 3.1)
project(XXX CXX)

set(OUT "main")
set(INCLUDE "inc")

include_directories(${INCLUDE})
file(GLOB SOURCE_FILES "src/*.cxx" "src/*.cpp" "src/*.c")
set(SOURCE ${SOURCE_FILES})

add_subdirectory(muscle)
add_subdirectory(tcpClient)

# 実行ファイルの作成を指示する
add_executable(${OUT} ${SOURCE})
target_link_libraries(${OUT} muscle tcpClient)