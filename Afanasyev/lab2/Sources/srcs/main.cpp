#include "../libs/main.h"

int main(int n, char **args)
{
    try
    {
        MyList listValues(args[2]);
        MyList listName(args[1]);
        std::cout << listName.calculateLogicExpr(listValues);
    }
    catch (const MyException &e)
    {
        std::cout << e << '\n';
    }

    return 0;
}