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
             * Document Node Tree
             */
            std::vector<Parser::Node> nodeTree = std::vector<Parser::Node>();



        public:
            /**
             * Creates Document Manager Instance
             */
            DocumentManager();



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



    } inline DocsManager;
}

#endif //DOCUMENTMANAGER_H
