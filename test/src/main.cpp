#include <stdinc.h>
#include "TestApp.h"


int main()
{
    try
    {
        BlockTestApp app;
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
