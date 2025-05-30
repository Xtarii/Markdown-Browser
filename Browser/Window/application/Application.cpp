#include "Application.h"

#include "search/SearchField.h"


void Browser::WindowUI::init(const HWND* parent, const HINSTANCE* process) {
    SearchField::create(parent, process);
}
