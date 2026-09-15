#import "cartridge.h"
#import "cartridge-header.h"
#include "tinyfiledialogs.h"

#include <limits.h>
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define AGNOSTIC_MAX_PATH MAX_PATH
#else
    #include <unistd.h>
    
    #if defined(PATH_MAX)
        #define AGNOSTIC_MAX_PATH PATH_MAX
    #else
        // Fallback for systems with infinite path maximums (like GNU/Hurd)
        #define AGNOSTIC_MAX_PATH 4096
    #endif
#endif


// 1 MB (original gameboy)
#define MAX_CART_SIZE (1024 * 1024)


bool cartridge_loaded = false;
uint8_t cartridge_data[MAX_CART_SIZE] = {0};
cartridge_header *cart_header = (cartridge_header*)(cartridge_data + CART_ENTRY_POINT);
char runtime_path_buffer[AGNOSTIC_MAX_PATH];

static bool get_runtime_path() {
#if defined(_WIN32)
    // Corrected Windows syntax: (BufferLength, BufferPointer)
    if (GetCurrentDirectoryA(AGNOSTIC_MAX_PATH, runtime_path_buffer) == 0) {
        return false;
    }
    return true;
    
#else
    // POSIX syntax: (BufferPointer, BufferLength)
    if (getcwd(runtime_path_buffer, AGNOSTIC_MAX_PATH) == NULL) {
        return false;
    }
    return true;
#endif
}

static bool load_catridge(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to load file: %s\n", filename);
        return false;
    }

    fseek(file, 0, SEEK_END);
    long long size = ftell(file);
    
    fseek(file, 0, SEEK_SET);

    long long bytes_to_read = (size > MAX_CART_SIZE) ? MAX_CART_SIZE : size;
    size_t bytes_read = fread(cartridge_data, 1, (size_t)bytes_to_read, file);
    
    fclose(file);

    if (bytes_read == 0 && bytes_to_read > 0) {
        printf("Error: Failed to read data from file: %s\n", filename);
        return false;
    }

    printf("ROM %s loaded, size: %lld bytes.\n", filename, size);
    return true;
}

bool open_cartridge_file(void) {
    if (!get_runtime_path()) {
        return false;
    }

    // Define acceptable extension filters
    const char *filterPatterns[] = { "*.nes", "*.bin", "*.rom" };

    // Automatically invokes Win32 on Windows, Zenity/GTK on Linux, and AppleScript on macOS
    const char *selected_path = tinyfd_openFileDialog(
        "Open Cartridge File",     // Title
        "",                        // Default path or directory
        3,                         // Number of filter patterns
        filterPatterns,            // Filter array
        "Cartridge Files",         // Filter description
        0                          // Allow multiple selection (0 = false)
    );

    if (selected_path != NULL) {
        load_catridge(selected_path);
        return true;
    }

    return false;
}

void print_cartidge_info() {
    
}
