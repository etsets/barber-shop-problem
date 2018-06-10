#include "customer.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Customer::Customer(std::string name, Shop* shop, Semaphore* barberNotifier, Semaphore* customersNotifier)
    :mCustomerName(name)
    ,pBelongsToShop(shop)
    ,mBarberNotifier(barberNotifier)
    ,mCustomersNotifier(customersNotifier)
{
    mCustomerThread = std::thread(operating, this);
    mCustomerThread.join();
}

Customer::~Customer()
{

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
    cout << "Customer : " << mCustomerName << " - getHaircut()\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Customer::balk()
{
    cout << "Customer : " << mCustomerName << " - balk()";
}

