#pragma once

#include <fstream>
#include <sstream>


inline std::string ReadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
