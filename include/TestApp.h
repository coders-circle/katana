#include <Application.h>

#include <iostream>


class TestApp: public Application
{
private:
    void OnRender()
    {
        std::cout<<"Hello World!"<<std::endl;
    }
};
