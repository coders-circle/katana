#include <stdinc.h>
#include <utils/Exception.h>

Exception::Exception(std::string errorMsg)
{
    m_errorMsg = errorMsg;
}

const char* Exception::what() const noexcept
{
    return m_errorMsg.c_str();
}
