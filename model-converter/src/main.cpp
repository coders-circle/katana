#include <stdinc.h>
#include <Model.h>


int main()
{
    try
    {
        Model m("models/homer.x");
        m.Save("bin/homer.out");
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
