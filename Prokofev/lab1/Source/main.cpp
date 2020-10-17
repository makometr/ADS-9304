#include <iostream>
#include <stdlib.h>

int f(int n)
{
    int sum = 0, i = 1, quantity = n - (n / 3);
    if ((n == 2) || (n == 1))
        return 1;
    while ((n / ++i) > 2)
        sum += f(n / i);
    sum += quantity;
    return sum;
}
int main(int argc, char* argv[])
{
    int res = 0;
    res = atoi(argv[1]);
    if (res < 1)
        std::cout << "not answer\n";
    else
        std::cout << f(res) << std::endl;
    return 0;
}
