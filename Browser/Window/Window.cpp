#include "Window.h"

#include <filesystem>

#include "../Browser.h"
#include "application/Application.h"



bool Browser::Window::registerClass(const HINSTANCE instance, const WNDPROC proc, const HBRUSH background) {
    WNDCLASSEX windowSpecs;

    // Settings
    windowSpecs.cbSize         = sizeof(WNDCLASSEX);
    windowSpecs.style          = CS_HREDRAW | CS_VREDRAW;
    windowSpecs.lpfnWndProc    = proc; // Window Proc ( Message Handler )
    windowSpecs.cbClsExtra     = 0;
    windowSpecs.cbWndExtra     = 0;
    windowSpecs.hInstance      = instance;
    windowSpecs.hIcon          = loadIcon(windowSpecs.hInstance);
    windowSpecs.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    windowSpecs.hbrBackground  = background; // Window Background Color
    windowSpecs.lpszMenuName   = nullptr;
    windowSpecs.lpszClassName  = winClass; // Window Class Name
    windowSpecs.hIconSm        = LoadIcon(windowSpecs.hInstance, IDI_APPLICATION);



    // Registers Window Class
    return RegisterClassEx(&windowSpecs);
}



HICON Browser::Window::loadIcon(const HINSTANCE instance) {
    return static_cast<HICON>(LoadImage(instance,
        getPath(&instance, "res/icons/icon.ico").string().c_str(), IMAGE_ICON,
        256, 256,
        LR_LOADFROMFILE
    ));
}



Browser::Window Browser::Window::createWindow(HINSTANCE instance, const int show) {
    HWND window = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        winClass, windowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1200, 800,
        nullptr,
        nullptr,
        instance,
        nullptr
    );
    if(!window) return Window(nullptr);


    // Window Setup
    WindowUI::init(&window, &instance);
    ShowWindow(window, show);
    UpdateWindow(window);
    return Window(window);
}

bool Browser::Window::isCreated() const {
    return instance != nullptr;
}





Browser::Window::Window(const HWND instance) {
    this->instance = instance;
}
