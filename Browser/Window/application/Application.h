#ifndef APPLICATION_H
#define APPLICATION_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * Window UI Namespace
 */
namespace Browser::WindowUI {
    /**
     * Initializes Application UI
     *
     * @param parent Parent Window
     * @param process Parent Process
     */
    void init(const HWND* parent, const HINSTANCE* process);
}

#endif //APPLICATION_H
