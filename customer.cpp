#include "customer.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Customer::Customer(std::string name, Shop* shop)
    :mCustomerName(name)
    ,pBelongsToShop(shop)
{
    mBarberNotifier = shop->getBarberSemaphore();
    mCustomersNotifier = shop->getCustomersSemaphore();
    mCustomerThread = std::thread(operating, this);
}

void Customer::operating()
{
    if (!pBelongsToShop->emptySeatsExist())
    {
        balk();
        return;
    }

    pBelongsToShop->addWaitingCustomer();
    mCustomersNotifier->Signal();
    mBarberNotifier->Wait();
    getHaircut();
}

void Customer::getHaircut()
{
    std::cout << "Customer : " << mCustomerName << " - getHaircut()\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Customer::balk()
{
    std::cout << "Customer : " << mCustomerName << " - balk()";
}

void Customer::joinThread()
{
    mCustomerThread.join();
}

