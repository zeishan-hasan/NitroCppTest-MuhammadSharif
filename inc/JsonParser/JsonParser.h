#pragma once

#include <string>

class JsonParserI
{
public:
    virtual ~JsonParserI() = default;
    virtual void Parse(const std::string& iFilePath) = 0;
};