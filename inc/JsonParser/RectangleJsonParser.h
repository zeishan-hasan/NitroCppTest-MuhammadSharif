#pragma once

#include "JsonParser/JsonParser.h"
#include "ShapeData/RectangleData.h"
#include <vector>
#include <nlohmann/json.hpp>

class RectangleJsonParserC : public JsonParserI
{
public:
    void Parse(const std::string& iFilePath) override;
    const std::vector<RectangleDataS>& GetShapes() const;

private:
    RectangleDataS ParseSingleShape(const nlohmann::json& iJson);
    std::vector<RectangleDataS> mShapes;
};