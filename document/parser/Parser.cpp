#include "Parser.h"

#include "../renderer/DocumentRenderer.h"

std::vector<Browser::Document::Parser::Node> Browser::Document::Parser::parseTree(const std::string& document) {
    std::vector<Node> tree;
    Node node {};

    for(int x = 0; x < document.length(); ) {
        const char c = document[x]; // Current character
        switch(c) {
            case ' ':
            case '\t':
                node.tree.push_back(space(&x, &c, document));
                break;

            case '\n':
            case '\r': // Parse New Line
                node.tree.push_back(newLine(&x,  &c, document));
                tree.push_back(node);
                node = Node{}; // Creates new Empty Node
                break;

            case '#': {
                if(node.type == NO_VALUE) {
                    const Node t = title(&x, &c, document);
                    node.type = TITLE;
                    node.value = t.value;
                    node.intValue = t.intValue;
                    break;
                }
            }

            case '-': {
                if(node.type == NO_VALUE) {
                    const Node t = list(&x, &c, document);
                    node.type = t.type;
                    node.value = t.value;
                    node.intValue = t.intValue;
                    break;
                }
            }


            case '*':
                node.tree.push_back(star(&x, &c, document));
                break;



            default: // Parse Word
                node.tree.push_back(word(&x, &c, document));
                if(node.type == NO_VALUE) node.type = PARAGRAPH;
                break;
        }
    }
    if(!node.tree.empty()) tree.push_back(node);
    return tree; // Adds Possibly last node and returns the parsed tree
}





Browser::Document::Parser::Node Browser::Document::Parser::space(int* x, const char* c, const std::string& document) {
    Node node{ .type = SPACE };

    int spaces = 0;
    std::string value;

    do {
        c = &document[*x];
        if(*c != ' ' && *c != '\t') break;


        if(*c == ' ') spaces++; // Space is always 1 but tab is defined in the renderer
        if(*c == '\t') spaces += TAB_WIDTH;
        value += *c; // Appends Character
        (*x)++;
    }while(*x < document.length());

    node.value = value;
    node.intValue = spaces;
    return node; // Returns Space Node
}

Browser::Document::Parser::Node Browser::Document::Parser::newLine(int* x, const char* c, const std::string& document) {
    Node node{ .type = NEWLINE };

    int lines = 0;
    std::string value;

    do {
        c = &document[*x];
        if(*c != '\r' && *c != '\n') break;

        if(*c == '\n') lines++;
        value += *c;
        (*x)++;
    }while(*x < document.length());

    node.value = value;
    node.intValue = lines;
    return node; // Returns New Line
}

Browser::Document::Parser::Node Browser::Document::Parser::title(int* x, const char* c, const std::string& document) {
    Node node { .type = TITLE };
    int size = 0;
    std::string value;

    do {
        c = &document[*x];
        if(*c != '#') break;
        if(size >= 6) break; // Can't go over Six in length technically

        value += *c;
        size++;
        (*x)++;
    }while(*x < document.length());

    node.value = value;
    node.intValue = size;
    return node; // Returns Title
}

Browser::Document::Parser::Node Browser::Document::Parser::star(int* x, const char* c, const std::string& document) {
    Node node{ .type = STAR };
    int size = 0;
    std::string value;

    do {
        c = &document[*x];
        if(*c != '*') break;
        if(size >= 2) break; // Can't go over 2 "*" in length

        value += *c;
        size++;
        (*x)++;
    }while(*x < document.length());

    node.value = value;
    node.intValue = size;
    return node;
}



Browser::Document::Parser::Node Browser::Document::Parser::list(int* x, const char* c, const std::string& document) {
    Node node{ .type = LIST, .value = "-" };
    node.intValue = static_cast<int>(node.value.length());

    if(document[(*x)++] == '-') {
        return node;
    }

    node.type = PARAGRAPH; // Normal Paragraph Detected
    return node;
}



Browser::Document::Parser::Node Browser::Document::Parser::word(int* x, const char* c, const std::string& document) {
    Node node { .type = WORD };
    std::string value;

    do {
        c = &document[*x];
        if(isSpecialCharacter(*c)) break;
        value += *c;
        (*x)++;
    }while(*x < document.length());

    node.value = value;
    node.intValue = static_cast<int>(value.length());
    return node; // Returns Word
}
