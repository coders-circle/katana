#pragma once

#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>


inline std::string ReadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


inline std::string ReadString(std::ifstream& file)
{
    unsigned int sz;
    file.read((char*)&sz, sizeof(sz));
    std::string s(sz+1, 0);
    file.read(&s[0], sz);
    return s;
}


inline std::string GetFolder(const std::string& path)
{
    std::string temp = path;

    size_t s = temp.find_last_of("/");
    if (s != std::string::npos)
        temp = temp.substr(0, s);

    return temp;
}


inline bool DoesFileExist(const std::string& path)
{
    return access(path.c_str(), F_OK) != -1;
}


class FileNotFoundError : public Exception
{
public:
    FileNotFoundError(const std::string& path) :
        Exception("Error: File not found\n\t" + path)
    {}
};
