#pragma once

#include <exception>
#include <string>


class Exception: public std::exception
{
public:
    Exception(std::string);
    const char* what() const noexcept;
protected:
    std::string m_errorMsg;
};
