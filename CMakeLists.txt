cmake_minimum_required(VERSION 3.20)
project(gameboy_emulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_XCODE_GENERATE_SCHEME ON)

find_package(SDL3 REQUIRED)

add_executable(emulator main.cpp)
target_link_libraries(emulator PRIVATE SDL3::SDL3)
