#include <iostream>
#include <vector>

#include <glaswegian++.h>

#define LEN 4096

int main()
{
    ghc_init();
    std::vector<double, GlaswegianAllocator<double>> xs;
    for(int i = 0; i < LEN; i++)
    {
        xs.emplace_back(i * i);
    }
    double s = 0;
    for(double i : xs)
    {
        s += i;
    }
    std::cout << s << std::endl;
    return 0;
}
