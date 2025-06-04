#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <vector>

#include "../parser/node/Node.h"


/**
 * Document Namespace
 */
namespace Browser::Document {
    /**
     * Document Manager
     */
    struct DocumentManager {
        private:
            /**
             * Scroll Offset
             */
            int scroll = 0;

            /**
             * Document Node Tree
             */
            std::vector<Parser::Node> nodeTree = std::vector<Parser::Node>();



        public:
            /**
             * Creates Document Manager Instance
             */
            DocumentManager();

            /**
             * Applies Scroll Offset to Document
             *
             * @param scroll New Scroll
             * @return Delta Scroll
             */
            int applyScroll(int scroll);



            /**
             * Loads Document
             *
             * @param document Document to Load
             * @return Load status
             */
            bool loadDocument(const char* document);

            /**
             * Loads Document that is located on this device
             *
             * @param path Path to Local Document
             * @return Load Status
             */
            bool loadDocument(const std::string& path);



            /**
             * Document Getter
             *
             * @return Document
             */
            [[nodiscard]] std::vector<Parser::Node> getDocument() const { return nodeTree; }

            /**
             * Document Scroll Offset
             *
             * @return Scroll Offset
             */
            [[nodiscard]] int getScroll() const { return scroll; }





            /**
             * Loads File from path
             *
             * @param path File Path
             * @param out File Content
             * @return Load Status
             */
            static bool loadFile(const std::string& path, std::string& out);



    } inline DocsManager;
}

#endif //DOCUMENTMANAGER_H
