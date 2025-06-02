cmake_minimum_required(VERSION 3.30)
project(Browser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /showIncludes")



# Third Party Libraries
include(FetchContent)
FetchContent_Declare(
        MDTP
        GIT_REPOSITORY https://github.com/Xtarii/MDTP.git
        GIT_TAG v1.2
)
FetchContent_MakeAvailable(MDTP)



# Browser files
add_executable(Browser main.cpp
        Browser/Window/Window.cpp
        Browser/Window/Window.h
        Browser/Browser.cpp
        Browser/Browser.h
        document/manager/DocumentManager.cpp
        document/manager/DocumentManager.h
        document/renderer/DocumentRenderer.cpp
        document/renderer/DocumentRenderer.h
        document/parser/Parser.cpp
        document/parser/Parser.h
        document/parser/node/Node.cpp
        document/parser/node/Node.h
        style/Style.cpp
        style/Style.h
        style/fonts/Fonts.cpp
        style/fonts/Fonts.h
        Browser/Window/components/inputs/Input.cpp
        Browser/Window/components/inputs/Input.h
        Browser/Window/components/Component.cpp
        Browser/Window/components/Component.h
        Browser/Window/application/Application.cpp
        Browser/Window/application/Application.h
        Browser/Window/application/search/SearchField.cpp
        Browser/Window/application/search/SearchField.h
        network/Network.cpp
        network/Network.h
)
set_target_properties(Browser PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_libraries(Browser PRIVATE MDTP)



# Custom Build Commands
add_custom_command(TARGET Browser POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Browser>/res)
