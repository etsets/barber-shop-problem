#include "shop.h"
#include <iostream>
#include <chrono>
#include <string>
#include <memory>
#include <cstdlib>

using namespace std;

int main()
{
    const int chairs = 10;
    Shop barberShop(chairs);
    std::vector< std::unique_ptr<Customer> > customers;

    int i;
    for (i = 0 ; i < 9 ; ++i)
    {
        Customer* newC = new Customer(std::to_string(i), &barberShop);
        customers.emplace_back(newC);
        newC->start();
        int milliSecondsToWait = std::rand() % 2000;
        std::this_thread::sleep_for(std::chrono::milliseconds(milliSecondsToWait));
    }

    for (; i < 15 ; ++i)
    {
        Customer* newC = new Customer(std::to_string(i), &barberShop);
        customers.emplace_back(newC);
        newC->start();
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    barberShop.stop();

    return 0;
}
