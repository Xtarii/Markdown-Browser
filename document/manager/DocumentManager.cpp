#include "DocumentManager.h"

#include "../parser/Parser.h"
#include "../../Browser/Browser.h"

#include <fstream>



Browser::Document::DocumentManager::DocumentManager() {
    loadDocument(std::string("res/pages/Home.md"));
}



bool Browser::Document::DocumentManager::loadDocument(const char* document) {
    nodeTree = Parser::parseTree(document);
    return true; // Status return
}



bool Browser::Document::DocumentManager::loadDocument(const std::string& path) {
    std::ifstream file = std::ifstream(path);
    if(!file.is_open()) {
        const char* document = "# Error\r\nCould not find " + *path.c_str();
        loadDocument(document);
        return false;
    }

    std::string full;
    std::string line;
    while(std::getline(file, line)) {
        full += "\r\n" + line;
    }
    file.close();
    return loadDocument(_strdup(full.c_str()));
}
