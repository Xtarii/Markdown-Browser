#include <tchar.h>
#include "Browser/Window/Window.h"
#include "document/renderer/DocumentRenderer.h"
#include "style/Style.h"



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previous, _In_ LPSTR CMDLine, _In_ int CMDShow) {
    if(!Browser::Window::registerClass(instance, WndProc)) { // Registers Window(s) Class
        MessageBox(nullptr, _T("Failed to register class!"), Browser::errorWindowTitle, NULL);
        return 1;
    }

    Browser::Window window = Browser::Window::createWindow(instance, CMDShow);
    if(!window.isCreated()) {
        MessageBox(nullptr, _T("Failed to create window!"), Browser::errorWindowTitle, NULL);
        return 1;
    }



    // Window Run Loop
    MSG msg;
    while(GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}




// Message Handler
LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT paintStruct;
    HDC context;

    switch(message) {
        case WM_PAINT: {
            context = BeginPaint(window, &paintStruct);

            Browser::Document::DocsRenderer.render(&context);

            EndPaint(window, &paintStruct);
            break;
        }



        case WM_COMMAND: // Update Command
            if(LOWORD(wParam) == UPDATE_WINDOW) {
                InvalidateRect(window, nullptr, true);
                UpdateWindow(window);
            }
            break;



        case WM_DESTROY:
            Browser::Style::clean(); // Application Cleanup
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(window, message, wParam, lParam);
    }

    return 0;
}
