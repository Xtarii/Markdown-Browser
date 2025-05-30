#ifndef WINDOW_H
#define WINDOW_H

/**
 * Window Update Message
 */
#define UPDATE_WINDOW 9001

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

namespace Browser {
    /**
     * Window Class
     */
    static TCHAR winClass[] = _T("Markdown Browser Window Class");

    /**
     * Window Title
     */
    static TCHAR windowTitle[] = _T("Mark Browser");

    /**
     * Error Window Title
     */
    static TCHAR errorWindowTitle[] = _T("Browser Error");





    /**
     * Window Class
     */
    class Window {
        /**
         * Window Instance
         */
        HWND instance;

        /**
         * Creates Window from Base Instance
         *
         * @param instance Base Instance
         */
        explicit Window(HWND instance);



    public:
        /**
         * Checks if this object was correctly created
         *
         * @return This Object Status
         */
        [[nodiscard]] bool isCreated() const;

        /**
         * Updates the Window if it has been created.
         */
        void update() const {
            if(isCreated()) UpdateWindow(instance);
        }





        /**
         * Registers Window Class
         *
         * If the registration was successful
         * the status returned will be **true**
         * otherwise it will be **false**
         *
         * @param instance Parent Instance
         * @param proc Window Message Handler
         * @param background Background Color
         * @return Class Register Status
         */
        static bool registerClass(_In_ HINSTANCE instance, _In_ WNDPROC proc, _In_ HBRUSH background = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));

        /**
         * Loads Icon
         *
         * @param instance Parent Instance
         * @return Loaded Icon
         */
        static HICON loadIcon(_In_ HINSTANCE instance);

        /**
         * Creates window
         *
         * Creates a window manager and returns the instance.
         *
         * @param instance Parent Instance
         * @param show Show Window
         * @return Custom Window
         */
        static Window createWindow(_In_ HINSTANCE instance, _In_ int show);
    };
}

#endif //WINDOW_H
