#include "SearchField.h"

#include <MDTP/core.h>

#include "../../Window.h"
#include "../../../../document/manager/DocumentManager.h"
#include "../../../../network/Network.h"
#include "../../components/inputs/Input.h"



void Browser::WindowUI::SearchField::create(const HWND* parent, const HINSTANCE* process) {
    RECT rect; // Gets Window Dimensions
    GetWindowRect(*parent, &rect);

    Components::Input input = Components::Input::create(
        parent, process,
        15, 15, rect.right - rect.left - 45, 20,
        1001 // Unique ID
    );

    handler = reinterpret_cast<WNDPROC>(SetWindowLongPtr(*input.getInstance(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(proc)));
}



LRESULT Browser::WindowUI::SearchField::proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if(msg == WM_KEYDOWN && wParam == VK_RETURN) {
        char buffer[MAX_PATH];
        GetWindowTextA(hwnd, buffer, MAX_PATH);
        search(std::string(buffer));

        // Update Window
        SendMessage(GetParent(hwnd), WM_COMMAND, UPDATE_WINDOW, reinterpret_cast<LPARAM>(hwnd));
        return 0;
    }
    if(msg == WM_CHAR && wParam == VK_RETURN) return 0; // Stops PING Sound
    return CallWindowProc(handler, hwnd, msg, wParam, lParam);
}



void Browser::WindowUI::SearchField::search(const std::string& query) {
    const Network::Query data = Network::parseQuery(query); // Parses Query
    MDTPObject object = Network::fetch( // Fetches Data
        data.address.address.c_str(), data.address.port == 0 ? MDTP_PORT : data.address.port,
        data.address.command.c_str()
    );

    // Loads Document
    std::cout << "Fetched Data: "
        << ((object.header.command.operation == STATUS_OK) ? "\033[38;5;10m" : "\033[38;5;9m")
        << object.header.toString()
        << "\033[0m"
        << std::endl;
    Document::DocsManager.loadDocument(object.body.c_str());
}
