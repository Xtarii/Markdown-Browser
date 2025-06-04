#ifndef PARSER_H
#define PARSER_H
#include <vector>

#include "node/Node.h"

/**
 * Document Parser Namespace
 */
namespace Browser::Document::Parser {
    /**
     * Parse Document into Node Tree
     *
     * @return Node Tree
     */
    std::vector<Node> parseTree(const std::string& document);



    /**
     * Parses Space Node from Document
     *
     * @param x Index Position in Document
     * @param c Current Character
     * @param document Base Document
     * @return Space Node
     */
    Node space(int* x, const char* c, const std::string& document);

    /**
     * Parses New Line Node
     *
     * @param x Index Position in Document
     * @param c Current Character
     * @param document Base Document
     * @return New Line Node
     */
    Node newLine(int* x, const char* c, const std::string& document);

    /**
     * Parses Word Node
     *
     * @param x Index Position in Document
     * @param c Current Character
     * @param document Base Document
     * @return Word Node
     */
    Node word(int* x, const char* c, const std::string& document);

    /**
     * Parse Title Node
     *
     * @param x Index Position in Document
     * @param c Current Character
     * @param document Base Document
     * @return Title Node
     */
    Node title(int* x, const char* c, const std::string& document);



    /**
     * Parse List Node
     *
     * @param x Index Position in Document
     * @param c Current Character
     * @param document Base Document
     * @return List Node
     */
    Node list(int* x, const char* c, const std::string& document);

    /**
     * Parse Star Node
     *
     * The star character is used to make **bold** and
     * **italic** text.
     *
     * @param x Index Position in Document
     * @param c Current Character
     * @param document Base Document
     * @return Star Node
     */
    Node star(int* x, const char* c, const std::string& document);





    /**
     * Compares the character to a special character and returns
     * if they match or not.
     *
     * @param c Character
     * @return Whether the character counts as special character
     */
    inline bool isSpecialCharacter(const char c) {
        return
            c == '\n' || c == '\r' || // New Line Markers
            c == ' ' || c == '\t'  || // Space Markers
            c == '*'; // Other Special Characters
    }
}

#endif //PARSER_H
