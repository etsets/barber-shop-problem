#include "customer.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Customer::Customer(std::string name, Shop* shop)
    :mCustomerName(name)
    ,pBelongsToShop(shop)
    ,mCustomerThread(nullptr)
{
    std::cout << "\n\nCustomer : " << mCustomerName << " - ctor \n";
}

Customer::~Customer()
{
    if (mCustomerThread)
    {
        mCustomerThread->join();
    }
}

void Customer::start()
{
    mCustomerThread.reset(new std::thread(&Customer::operating, this));
}

void Customer::operating()
{
    if (!pBelongsToShop->takeSeat(this))
    {
        balk();
        return;
    }

    std::cout << "Customer : - operating... Before signal \n";
    pBelongsToShop->getCustomersSemaphore()->Signal();
    pBelongsToShop->getBarberSemaphore()->Wait();
    getHaircut();
}

void Customer::getHaircut()
{
    std::cout << "Customer : " << mCustomerName << " - getHaircut()\n";
}

void Customer::balk()
{
    std::cout << "Customer : " << mCustomerName << " - balk()\n";
}


