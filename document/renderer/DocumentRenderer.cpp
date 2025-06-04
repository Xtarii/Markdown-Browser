#include "DocumentRenderer.h"

#include "../../style/fonts/Fonts.h"
#include "../manager/DocumentManager.h"



void Browser::Document::Renderer::resetPosition() {
    x = X_START; y = Y_START + DocsManager.getScroll();
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
    RECT window; // Window Reference
    GetWindowRect(WindowFromDC(*context), &window);

    Style::Fonts::Font font = Style::Fonts::Font(
        BASE_TITLE_HEIGHT - (node->intValue * TITLE_SIZE_DIFFERENCE),
        false, false, false, FW_HEAVY, "Segoe UI"
    );
    SelectObject(*context, font.object);
    for(const Parser::Node& sub : node->tree) {
        switch(sub.type) {
            case Parser::SPACE:
                x += sub.intValue * SPACE_WIDTH;
                break;
            case Parser::NEWLINE: { // Draws Title Line Under Title before new lines
                y += font.height + LINE_SPACE;
                const RECT line{
                    .left = X_START, .top = y,
                    .right = ((TITLE_LINE_WIDTH_ADDER + 1) * (window.right - window.left)) / (TITLE_LINE_WIDTH_ADDER * TITLE_LINE_WIDTH),
                    .bottom = y + LINE_SPACE,
                };
                FillRect(*context, &line, reinterpret_cast<HBRUSH>((COLOR_WINDOW - 1)));
                y += sub.intValue * BASE_TEXT_HEIGHT;
                x = X_START;
                break;
            }

            // Prints Title
            case Parser::LIST:
            case Parser::STAR:
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
    bold = false; italic = false;
}

void Browser::Document::Renderer::paragraph(const HDC* context, const Parser::Node* node) {
    for(const Parser::Node& sub : node->tree) {
        Style::Fonts::Font font = Style::Fonts::Font(
            BASE_TEXT_HEIGHT,
            false, italic, false, bold ? FW_BOLD : FW_NORMAL,
            (bold || italic) ? "Arial" : "Segoe UI"
        );
        SelectObject(*context, font.object);



        switch(sub.type) {
            case Parser::SPACE:
                x += sub.intValue * SPACE_WIDTH;
                break;
            case Parser::NEWLINE:
                y += BASE_TEXT_HEIGHT + (LINE_SPACE * (sub.intValue - 1) * BASE_TEXT_HEIGHT);
                x = X_START;
                break;

            case Parser::LIST:
            case Parser::TITLE:
            case Parser::WORD: {
                TextOut(*context, x, y, sub.value.c_str(), static_cast<int>(sub.value.length()));

                SIZE size;
                GetTextExtentPoint32A(*context, sub.value.c_str(), static_cast<int>(sub.value.length()), &size);
                x += size.cx;
                break;
            }



            case Parser::STAR: {
                if(sub.intValue == 1) italic = !italic;
                if(sub.intValue == 2) bold = !bold;
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
    x = X_START + TAB_WIDTH * SPACE_WIDTH;

    Style::Fonts::Font startFont = Style::Fonts::Font(
        BASE_TEXT_HEIGHT,
        false, italic, false, bold ? FW_BOLD : FW_NORMAL,
        (bold || italic) ? "Arial" : "Segoe UI"
    );
    SelectObject(*context, startFont.object);

    // List sign
    const int line = y + BASE_TEXT_HEIGHT / 2;
    Ellipse(*context, x - 3, line - 3, x + 3, line + 3);
    x += 5;

    // List content
    for(const Parser::Node& sub : node->tree) {
        Style::Fonts::Font font = Style::Fonts::Font(
            BASE_TEXT_HEIGHT,
            false, italic, false, bold ? FW_BOLD : FW_NORMAL,
            (bold || italic) ? "Arial" : "Segoe UI"
        );
        SelectObject(*context, font.object);



        switch(sub.type) {
            case Parser::SPACE:
                x += sub.intValue * SPACE_WIDTH;
                break;
            case Parser::NEWLINE:
                y += font.height + (LINE_SPACE * (sub.intValue - 1) * BASE_TEXT_HEIGHT);
                x = X_START;
                break;

            case Parser::TITLE:
            case Parser::WORD: {
                TextOut(*context, x, y, sub.value.c_str(), static_cast<int>(sub.value.length()));

                SIZE size;
                GetTextExtentPoint32A(*context, sub.value.c_str(), static_cast<int>(sub.value.length()), &size);
                x += size.cx;
                break;
            }



            case Parser::STAR: {
                if(sub.intValue == 1) italic = !italic;
                if(sub.intValue == 2) bold = !bold;
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
