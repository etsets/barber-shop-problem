#include "shop.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace std;

int main()
{
    const int chairs = 10;
    Shop barberShop(chairs);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    int i;
    for (i = 0 ; i < 9 ; ++i)
    {
        Customer* newC = new Customer(std::to_string(i), &barberShop);
        barberShop.newCustomerArrives(newC);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (; i < 15 ; ++i)
    {
        Customer* newC = new Customer(std::to_string(i), &barberShop);
        barberShop.newCustomerArrives(newC);
    }

    barberShop.stop();

    return 0;
}
