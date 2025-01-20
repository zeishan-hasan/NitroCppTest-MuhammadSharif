add_executable(RectangleUnitTests
    RectangleTest.cpp
)

target_link_libraries(RectangleUnitTests
    PRIVATE
        RectangleLib
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME RectangleUnitTests COMMAND RectangleUnitTests)

add_executable(RectangleJsonParserUnitTests
    RectangleJsonParserTest.cpp
)

target_link_libraries(RectangleJsonParserUnitTests
    PRIVATE
        JsonParserLib
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME RectangleJsonParserUnitTests COMMAND RectangleJsonParserUnitTests)