#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

namespace Browser::Document::Parser {
    /**
     * Node Type
     */
    enum NodeType {
        /**
         * No Value Type
         *
         * Used to indicate unknown or
         * not yet selected type for
         * the node.
         */
        NO_VALUE,

        /**
         * Title Node
         *
         * Single line node with big text
         */
        TITLE,

        /**
         * Paragraph Node
         *
         * Normal Text Node. Seperated by line in the
         * documents text.
         */
        PARAGRAPH,



        /**
         * Word Node Type
         *
         * No specific type, just words
         * that together builds the documents
         * **Titles** and **Paragraphs** and more.
         */
        WORD,

        /**
         * Space Node
         *
         * Represents a space in the
         * document text.
         */
        SPACE,

        /**
         * New Line Node
         *
         * Represents a new line
         * in the document text.
         */
        NEWLINE,
    };



    /**
     * Document Node Object
     */
    struct Node {
        /**
         * Node Type
         */
        NodeType type = NO_VALUE;

        /**
         * Node Integer value
         */
        int intValue;

        /**
         * Node Value
         */
        std::string value;

        /**
         * Node Tree
         */
        std::vector<Node> tree;





        /**
         * Converts this Node Object to a
         * string representation.
         *
         * @return String Object
         */
        [[nodiscard]] std::string toString() const {
            return std::string(
                "{ "
                "value: " + value +
                ", int: " + std::to_string(intValue) +
                ", tree: " + std::to_string(tree.size()) +
                ", type: " + std::to_string(type) +
                " }"
            );
        }
    };
}

#endif //NODE_H
