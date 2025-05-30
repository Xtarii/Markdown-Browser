#ifndef INPUT_H
#define INPUT_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../Component.h"

namespace Browser::WindowUI::Components {
    /**
     * Input Component
     */
    class Input : public Component {
        /**
         * Creates Input Component
         *
         * @param instance Component Instance
         */
        explicit Input(const HWND* instance) : Component(instance) {}



        public:
            /**
             * Creates Input Component
             *
             * @param parent Parent
             * @param process Process
             * @param x X Position
             * @param y Y Position
             * @param width Width
             * @param height Height
             * @param ID ID
             * @return Input
             */
            static Input create(const HWND* parent, const HINSTANCE* process, int x, int y, int width, int height, int ID);
    };
}

#endif //INPUT_H
