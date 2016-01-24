#include <stdinc.h>
#include <TestApp.h>


int main()
{
    try
    {
        TestApp app;
        
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
