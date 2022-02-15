cmake_minimum_required(VERSION 3.1.2)

project(ClipApp)

set(APP_SOURCES clipapp.cpp)

if(WIN32)
    list(APPEND APP_SOURCES app_win.cpp)
elseif(APPLE)
    add_definitions(-fobjc-arc)
    list(APPEND APP_SOURCES app_mac.mm)
endif()

add_executable(ClipApp ${APP_SOURCES})

if(APPLE)
    find_library(APPKIT_LIBRARY Appkit)
    target_link_libraries(ClipApp ${APPKIT_LIBRARY})
endif()