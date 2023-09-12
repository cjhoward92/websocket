cmake_minimum_required(VERSION 3.26)
project(websocket)

# Load Catch2 for testing
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
# Done with Catch2

set(CMAKE_CXX_STANDARD 20)

add_executable(websocket main.cpp
        client/client.cpp
        client/client.h)

# These tests can use the Catch2-provided main
add_executable(tests client/client_tests.cpp
        client/client.cpp
        client/client.h
        utilities/base64.cpp
        utilities/base64.h
        utilities/base64_tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)