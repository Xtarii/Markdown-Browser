#ifndef SEARCHFIELD_H
#define SEARCHFIELD_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

/**
 * Application SearchField
 */
namespace Browser::WindowUI::SearchField {
    /// Search Input Handler
    inline WNDPROC handler;

    /// Search Input Process Handler
    LRESULT CALLBACK proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



    /**
     * Creates Search Field Component
     *
     * @param parent Search Field Parent
     * @param process Search Field Process
     */
    void create(const HWND* parent, const HINSTANCE* process);



    /**
     * Performs a search request for
     * the given query.
     *
     * @param query Search Query
     */
    void search(const std::string& query);
}

#endif //SEARCHFIELD_H
