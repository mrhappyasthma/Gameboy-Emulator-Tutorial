cmake_minimum_required(VERSION 3.20)
project(gameboy_emulator CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_XCODE_GENERATE_SCHEME ON)

find_package(SDL3 REQUIRED)

# Tinyfile Dialogs
set(TINYFD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/tinyfiledialogs")
add_executable(emulator 
    main.cpp
    cartridge-header.h
    "${TINYFD_DIR}/tinyfiledialogs.c"
)

target_include_directories(emulator PRIVATE "${TINYFD_DIR}")

# Link dependencies
target_link_libraries(emulator PRIVATE SDL3::SDL3)

if(WIN32)
    # Windows requires explicit linkage to the Win32 common dialog API libraries
    target_link_libraries(emulator PRIVATE comdlg32 ole32 user32 shell32)
endif()

