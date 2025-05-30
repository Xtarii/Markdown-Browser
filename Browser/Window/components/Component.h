#ifndef COMPONENT_H
#define COMPONENT_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * Components Namespace
 */
namespace Browser::WindowUI::Components {
    /**
     * Component Base Class
     */
    class Component {
        /// Component Instance
        HWND instance;



        public:
            /// Creates Base Component
            explicit Component(const HWND* instance) { this->instance = *instance; }



            /**
             * Gets Component Instance
             *
             * @return Component Instance
             */
            HWND* getInstance() { return &instance; };
    };
}

#endif //COMPONENT_H
