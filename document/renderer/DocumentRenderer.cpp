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
