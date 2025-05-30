#include "Fonts.h"

Browser::Style::Fonts::Font::Font(int height, DWORD underline, DWORD italic, DWORD strikeOut, int weight, LPCSTR fontFamily) {
    object = CreateFontA(
        height, 0, // Sets Height with automatic with
        0, 0, weight,
        italic, underline, strikeOut, DEFAULT_CHARSET,

        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        VARIABLE_PITCH, fontFamily
    );
    this->height = height;
}



Browser::Style::Fonts::Font::~Font() {
    DeleteObject(object); // Cleanup of font
}
