#include "shop.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace std;

int main()
{
    const int chairs = 10;
    Shop barberShop(chairs);

    int i;
    for (i = 0 ; i < 9 ; ++i)
    {
        barberShop.newCustomerArrives(std::to_string(i));
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (; i < 15 ; ++i)
    {
        barberShop.newCustomerArrives(std::to_string(i));
    }

    barberShop.joinThreads();

    return 0;
}
