#include "DocumentRenderer.h"

#include "../../style/fonts/Fonts.h"
#include "../manager/DocumentManager.h"



void Browser::Document::Renderer::resetPosition() {
    x = X_START; y = Y_START;
}


void Browser::Document::Renderer::render(const HDC* context) {
    resetPosition(); // Resets Position before rendering
    std::vector<Parser::Node> tree = DocsManager.getDocument();
    for(const Parser::Node& node : tree) {
        if(node.type == Parser::PARAGRAPH) paragraph(context, &node); // Paragraph Text
        if(node.type == Parser::TITLE) title(context, &node); // Title Text
        if(node.type == Parser::LIST) list(context, &node); // List Node
    }
    resetPosition(); // Resets Position for next rendering
}





void Browser::Document::Renderer::title(const HDC* context, const Parser::Node* node) {
    Style::Fonts::Font font = Style::Fonts::Font(BASE_TITLE_HEIGHT - (node->intValue * TITLE_SIZE_DIFFERENCE));
    SelectObject(*context, font.object);
    for(const Parser::Node& sub : node->tree) {
        switch(sub.type) {
            case Parser::SPACE:
                x += sub.intValue * SPACE_WIDTH;
                break;
            case Parser::NEWLINE:
                y += font.height + LINE_SPACE;
                x = X_START;
                break;
            case Parser::WORD: {
                TextOut(*context, x, y, sub.value.c_str(), static_cast<int>(sub.value.length()));

                SIZE size;
                GetTextExtentPoint32A(*context, sub.value.c_str(), static_cast<int>(sub.value.length()), &size);
                x += size.cx;
                break;
            }



            default: // No Node Type found
                break;
        }
    }


    // Window Reference
    RECT window;
    GetWindowRect(WindowFromDC(*context), &window);


    // Draw Linje
    const RECT line{
        .left = X_START,
        .top = y,

        .right = ((TITLE_LINE_WIDTH_ADDER + 1) * (window.right - window.left)) / (TITLE_LINE_WIDTH_ADDER * TITLE_LINE_WIDTH),
        .bottom = y + LINE_SPACE,
    };
    FillRect(*context, &line, reinterpret_cast<HBRUSH>((COLOR_WINDOW - 1)));
    y += font.height / 2 + LINE_SPACE;
}

void Browser::Document::Renderer::paragraph(const HDC* context, const Parser::Node* node) {
    SelectObject(*context, Style::Fonts::Paragraph.object);
    for(const Parser::Node& sub : node->tree) {
        switch(sub.type) {
            case Parser::SPACE:
                x += sub.intValue * SPACE_WIDTH;
                break;
            case Parser::NEWLINE:
                y += Style::Fonts::Paragraph.height + LINE_SPACE;
                x = X_START;
                break;
            case Parser::WORD: {
                TextOut(*context, x, y, sub.value.c_str(), static_cast<int>(sub.value.length()));

                SIZE size;
                GetTextExtentPoint32A(*context, sub.value.c_str(), static_cast<int>(sub.value.length()), &size);
                x += size.cx;
                break;
            }



            case Parser::PARAGRAPH: // This should never happen
                paragraph(context, &sub);
                break;
            default: // No Node Type found
                break;
        }
    }
}

void Browser::Document::Renderer::list(const HDC* context, const Parser::Node* node) {
    SelectObject(*context, Style::Fonts::Paragraph.object);
    x = X_START + TAB_WIDTH * SPACE_WIDTH;

    // List sign
    const int line = y + Style::Fonts::Paragraph.height / 2;
    Ellipse(*context, x - 5, line - 5, x + 5, line + 5);
    x += 7;

    // List content
    for(const Parser::Node& sub : node->tree) {
        switch(sub.type) {
            case Parser::SPACE:
                x += sub.intValue * SPACE_WIDTH;
                break;
            case Parser::NEWLINE:
                y += Style::Fonts::Paragraph.height + LINE_SPACE;
                x = X_START;
                break;

            case Parser::WORD: {
                TextOut(*context, x, y, sub.value.c_str(), static_cast<int>(sub.value.length()));

                SIZE size;
                GetTextExtentPoint32A(*context, sub.value.c_str(), static_cast<int>(sub.value.length()), &size);
                x += size.cx;
                break;
            }




            case Parser::LIST: // Should never happen
                list(context, &sub);
                break;
            default: // No Node Type found
                break;
        }
    }
}
