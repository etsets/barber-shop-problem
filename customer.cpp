#include "customer.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Customer::Customer(std::string name, Shop* shop)
    :mCustomerName(name)
    ,pBelongsToShop(shop)
    ,mTerminated(false)
{
    std::cout << "\n\nCustomer : " << mCustomerName << " - ctor \n";
    operating();
}

void Customer::operating()
{
    if (!pBelongsToShop->takeSeat(this))
    {
        balk();
        mTerminated = true;
        return;
    }

    std::cout << "Customer : - operating... Before signal \n";
    pBelongsToShop->getCustomersSemaphore()->Signal();
    pBelongsToShop->getBarberSemaphore()->Wait();
    getHaircut();
    mTerminated = true;
}

void Customer::getHaircut()
{
    std::cout << "Customer : " << mCustomerName << " - getHaircut()\n";
    //std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Customer::balk()
{
    std::cout << "Customer : " << mCustomerName << " - balk()\n";
}


