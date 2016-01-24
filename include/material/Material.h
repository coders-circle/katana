#pragma once
#include <material/Program.h>


class Material
{
public:
    virtual void Use() = 0;

protected:
    Program m_program;
};
