cmake_minimum_required(VERSION 3.14)
project(NitroTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)

find_package(GTest QUIET)
if(NOT GTest_FOUND)
    message(STATUS "GTest not found. Fetching from GitHub...")
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    # Prevent overriding parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found. Fetching from GitHub...")
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

add_library(RectangleLib
    src/Rectangle.cpp
)

target_include_directories(RectangleLib
    PUBLIC ${PROJECT_SOURCE_DIR}/inc
)

add_library(JsonParserLib
    src/RectangleJsonParser.cpp
)

target_include_directories(JsonParserLib
    PUBLIC ${PROJECT_SOURCE_DIR}/inc
)

target_link_libraries(JsonParserLib
    PUBLIC
        RectangleLib
        nlohmann_json::nlohmann_json
)

add_executable(Rectangle src/main.cpp)
target_link_libraries(Rectangle
    PRIVATE 
        RectangleLib 
        JsonParserLib
)

add_subdirectory(test)