#include "Browser.h"

std::filesystem::path Browser::getPath(const HINSTANCE* instance, const char* path) {
    char buffer[MAX_PATH];
    GetModuleFileNameA(*instance, buffer, MAX_PATH);
    return static_cast<std::filesystem::path>(buffer).parent_path() / path;
}
