#ifndef DOCUMENTRENDERER_H
#define DOCUMENTRENDERER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../parser/node/Node.h"

/**
 * Space Width
 */
#define SPACE_WIDTH 5
/**
 * Tab Width ( How many spaces one tab is )
 */
#define TAB_WIDTH 4

/**
 * Line Space
 */
#define LINE_SPACE 2

/**
 * The Procent of the Window Width that the titles line with will fill
 */
#define TITLE_LINE_WIDTH 2

/**
 * Magic Number : HELP THIS IS OUT OF CONTROL
 */
#define TITLE_LINE_WIDTH_ADDER 5

/**
 * Y Position Start
 */
#define Y_START 50
/**
 * X Position Start
 */
#define X_START 15



namespace Browser::Document {
    /**
     * Document Renderer
     */
    struct Renderer {
        private:
            /**
             * Basic Font Styles
             */
            bool bold = false, italic = false;

            /**
             * Render Position
             */
            int x = 0, y = 0;



            /**
             * Resets Position
             */
            void resetPosition();





        public:
            /**
             * Simple Document Renderer
             *
             * @param context Application Context
             */
            void render(const HDC* context);



            /**
             * Renders Paragraph
             *
             * @param context Application Context
             * @param node Paragraph Node
             */
            void paragraph(const HDC* context, const Parser::Node* node);



            /**
             * Renders Title Node
             *
             * @param context Application Context
             * @param node Title Node
             */
            void title(const HDC* context, const Parser::Node* node);



            /**
             * Renders List Node
             *
             * @param context Application Context
             * @param node List Node
             */
            void list(const HDC* context, const Parser::Node* node);



    } inline DocsRenderer;
}

#endif //DOCUMENTRENDERER_H
