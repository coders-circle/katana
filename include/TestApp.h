#include <Application.h>

#include <iostream>


class TestApp: public Application
{
private:
    void OnRender()
    {
    }

    void OnUpdate(float dt)
    {
        std::cout << dt << " seconds passed" << std::endl;
    }
};
