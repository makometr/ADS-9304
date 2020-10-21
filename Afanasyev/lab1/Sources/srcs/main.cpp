#include "../libs/main.h"

int main(int amount, char **args)
{
    std::string strToCheck;

    std::ifstream file;
    file.open(args[1], std::ios_base::in);

    std::getline(file, strToCheck);

    file.close();

    Analyzer analyzer(strToCheck);
    std::cout << analyzer() << '\n';

    return 0;
}