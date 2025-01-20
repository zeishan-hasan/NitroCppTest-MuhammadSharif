#include "JsonParser/RectangleJsonParser.h"
#include <fstream>
#include <sstream>

void RectangleJsonParserC::Parse(const std::string& iFilePath)
{
    // For fresh start
    mShapes.clear();

    std::ifstream file(iFilePath);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + iFilePath);
    }

    // Read entire file into string
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    // Parse JSON
    nlohmann::json jsonData;
    try 
    {
        jsonData = nlohmann::json::parse(buffer.str());
    }
    catch (const nlohmann::json::parse_error& e)
    {
        throw std::runtime_error("Invalid JSON format in file: " + iFilePath);
    }

    // Check existense of array
    if (!jsonData.contains("rects") || !jsonData["rects"].is_array())
    {
        throw std::invalid_argument("JSON must contain 'rects' array");
    }

    // Parse all rectangles
    for (const auto& rectJson : jsonData["rects"])
    {
        mShapes.push_back(ParseSingleShape(rectJson));
    }
}

RectangleDataS RectangleJsonParserC::ParseSingleShape(const nlohmann::json& iJson)
{
    // Validate fields
    const char* requiredFields[] = {"x", "y", "w", "h"};
    for (const auto& field : requiredFields)
    {
        if (!iJson.contains(field))
        {
            throw std::invalid_argument(std::string("Missing required field: ") + field);
        }
        if (!iJson[field].is_number())
        {
            throw std::invalid_argument(std::string("Field must be numeric: ") + field);
        }
    }

    // Validate dimensions
    if ((iJson["w"].get<int32_t>() < 0) || (iJson["h"].get<int32_t>() < 0))
    {
        throw std::invalid_argument("Width and height must be non-negative");
    }

    return RectangleDataS{
        iJson["x"].get<int32_t>(),
        iJson["y"].get<int32_t>(),
        iJson["w"].get<int32_t>(),
        iJson["h"].get<int32_t>()
    };
}

const std::vector<RectangleDataS>& RectangleJsonParserC::GetShapes() const
{
    return mShapes;
}