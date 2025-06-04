#include "Style.h"

#include <iostream>
#include <windows.h>

#include "fonts/Fonts.h"


void Browser::Style::clean() {
    std::cout << "Style Cleanup \033[38;5;9m[...]\033[0m" << std::endl;
}
