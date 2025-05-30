#include "Input.h"



Browser::WindowUI::Components::Input Browser::WindowUI::Components::Input::create(const HWND* parent, const HINSTANCE* process, int x, int y, int width, int height, int ID) {
    HWND instance = CreateWindow("Edit", nullptr,
        WS_BORDER | WS_CHILD | WS_VISIBLE, // Style
        x, y, width, height,
        *parent, reinterpret_cast<HMENU>(ID), *process, nullptr
    );
    return Input(&instance); // Creates Input Instance and returns it
}
