#include "Fonts.h"

#include <iostream>

Browser::Style::Fonts::Font Browser::Style::Fonts::Title = Font(BASE_TITLE_HEIGHT, false, false, false, FW_NORMAL, "Segeo UI");
Browser::Style::Fonts::Font Browser::Style::Fonts::Paragraph = Font(BASE_TEXT_HEIGHT, false, false, false, FW_NORMAL, "Segeo UI");

Browser::Style::Fonts::Font::Font(int height, DWORD underline, DWORD italic, DWORD strikeOut, int weight, LPCSTR fontFamily) {
    object = CreateFontA(
        height, 0, // Sets Height with automatic with
        0, 0, weight,
        italic, underline, strikeOut, DEFAULT_CHARSET,

        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        FF_MODERN, fontFamily
    );
    this->height = height;
}



Browser::Style::Fonts::Font::~Font() {
    std::cout << "Font Cleanup:\n\033[38;5;9m - Deletes font\033[0m" << std::endl;
    DeleteObject(object); // Cleanup of font
}
