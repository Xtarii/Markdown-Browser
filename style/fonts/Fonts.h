#ifndef FONTS_H
#define FONTS_H

#include <windows.h>

/**
 * Base Title Height
 */
#define BASE_TITLE_HEIGHT 50
/**
 * Title Size Difference
 */
#define TITLE_SIZE_DIFFERENCE 6

/**
 * Base Text Height
 */
#define BASE_TEXT_HEIGHT 20



/**
 * Default Browser Fonts
 */
namespace Browser::Style::Fonts {
    /**
     * Font Object
     */
    struct Font {
        /**
         * Font Height
         */
        int height = BASE_TEXT_HEIGHT;

        /**
         * Font Object
         */
        HFONT object;


        /**
         * Creates Font Object
         *
         * @param height Font Height
         * @param underline Underline text
         * @param italic Italic text
         * @param strikeOut Strike Out text
         * @param weight Font Weight
         * @param fontFamily Font Family
         */
        explicit Font(
            int height,
            DWORD underline = false, DWORD italic = false, DWORD strikeOut = false,
            int weight = FW_DONTCARE,
            LPCSTR fontFamily = "Segoe UI"
        );

        /// Font Cleanup
        ~Font();
    };



    /**
     * Title Font
     */
    inline Font Title = Font(BASE_TITLE_HEIGHT);

    /**
     * Paragraph Font
     */
    inline Font Paragraph = Font(BASE_TEXT_HEIGHT);
}

#endif //FONTS_H
