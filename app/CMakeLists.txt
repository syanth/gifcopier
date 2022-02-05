cmake_minimum_required(VERSION 3.1.2)

project(ClipApp)

set(APP_SOURCES clipapp.cpp)

if(WIN32)
    list(APPEND APP_SOURCES app_win.cpp)
endif()

add_executable(ClipApp ${APP_SOURCES})