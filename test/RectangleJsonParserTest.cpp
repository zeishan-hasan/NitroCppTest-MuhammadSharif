#include "JsonParser/RectangleJsonParser.h"
#include <gtest/gtest.h>
#include <fstream>
#include <memory>

class RectangleJsonParserTest : public ::testing::Test 
{
protected:
    void CreateTestFile()
    {
        const char* jsonContent = R"({
            "rects": [
                {"x": 100, "y": 100, "w": 250, "h": 80},
                {"x": 120, "y": 200, "w": 250, "h": 150}
            ]
        })";
        
        mTestFilePath = "TestRectangles.json";
        std::ofstream file(mTestFilePath);
        file << jsonContent;
        file.close();
    }

    void CreateInvalidJsonFile()
    {
        std::ofstream file("Invalid.json");
        file << "{ invalid json content }";
        file.close();
    }

    void CreateMissingArrayFile()
    {
        std::ofstream file("MissingArray.json");
        file << R"({"other": "content"})";
        file.close();
    }

    std::string mTestFilePath;
    std::unique_ptr<RectangleJsonParserC> mParser;
    
    void SetUp() override 
    {
        mParser = std::make_unique<RectangleJsonParserC>();
        CreateTestFile();
    }

    void TearDown() override 
    {
        std::remove(mTestFilePath.c_str());
    }
};

TEST_F(RectangleJsonParserTest, ParseValidFile) 
{
    mParser->Parse(mTestFilePath);
    const auto& shapes = mParser->GetShapes();
    
    ASSERT_EQ(shapes.size(), 2);
    
    // Verify first rectangle 
    EXPECT_EQ(shapes[0].x, 100);
    EXPECT_EQ(shapes[0].y, 100);
    EXPECT_EQ(shapes[0].width, 250);
    EXPECT_EQ(shapes[0].height, 80);
    
    // Verify second rectangle 
    EXPECT_EQ(shapes[1].x, 120);
    EXPECT_EQ(shapes[1].y, 200);
    EXPECT_EQ(shapes[1].width, 250);
    EXPECT_EQ(shapes[1].height, 150);
}

TEST_F(RectangleJsonParserTest, HandleNonExistentFile) 
{
    EXPECT_THROW(
        mParser->Parse("NonExistent.json"),
        std::runtime_error
    );
}

TEST_F(RectangleJsonParserTest, HandleInvalidJson) 
{
    CreateInvalidJsonFile();
    
    EXPECT_THROW(
        mParser->Parse("Invalid.json"),
        std::runtime_error
    );
    
    std::remove("Invalid.json");
}

TEST_F(RectangleJsonParserTest, HandleMissingRectsArray) 
{
    CreateMissingArrayFile();
    
    EXPECT_THROW(
        mParser->Parse("MissingArray.json"),
        std::invalid_argument
    );
    
    std::remove("MissingArray.json");
}

TEST_F(RectangleJsonParserTest, HandleInvalidRectangleData) 
{
    const char* invalidJson = R"({
        "rects": [
            {"x": 100, "y": 100, "w": -250, "h": 80}
        ]
    })";
    
    std::string invalidFilePath = "InvalidRect.json";
    std::ofstream file(invalidFilePath);
    file << invalidJson;
    file.close();
    
    EXPECT_THROW(
        mParser->Parse(invalidFilePath),
        std::invalid_argument
    );
    
    std::remove(invalidFilePath.c_str());
}

TEST_F(RectangleJsonParserTest, HandleEmptyRectanglesArray) 
{
    const char* emptyJson = R"({"rects": []})";
    
    std::string emptyFilePath = "EmptyArray.json";
    std::ofstream file(emptyFilePath);
    file << emptyJson;
    file.close();
    
    mParser->Parse(emptyFilePath);
    EXPECT_TRUE(mParser->GetShapes().empty());
    
    std::remove(emptyFilePath.c_str());
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}