cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(ClipApp)

set(APP_SOURCES "")

if(WIN32)
    list(APPEND APP_SOURCES app_win.cpp)
elseif(APPLE)
    add_definitions(-fobjc-arc)
    list(APPEND APP_SOURCES app_mac.mm)
endif()

add_executable(ClipApp clipapp.cpp ${APP_SOURCES})

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit)
    target_link_libraries(ClipApp ${APPKIT_LIBRARY})
endif()

##################
### TEST SETUP ###
##################

enable_testing()
# Download Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/ea55f1f52c489535f0d3b583c81529762c9cb5ea.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(app_test app_test.cpp ${APP_SOURCES})
target_link_libraries(app_test gtest_main)
if(APPLE)
    target_link_libraries(app_test ${APPKIT_LIBRARY})
endif()

include(GoogleTest)
gtest_discover_tests(app_test)