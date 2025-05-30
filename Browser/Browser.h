#ifndef BROWSER_H
#define BROWSER_H

#include <windows.h>
#include <filesystem>

/**
 * Browser Namespace
 */
namespace Browser {
    /**
     * Gets path to file local to the runtime path
     *
     * @param instance Process Instance
     * @param path Path to file
     * @return Full path
     */
    std::filesystem::path getPath(const HINSTANCE* instance, const char* path);
}

#endif //BROWSER_H
