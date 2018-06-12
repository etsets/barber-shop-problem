#include "barber.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Barber::Barber(Shop* shop)
    :mAlive(true)
    ,pBelongsToShop(shop)
{
    mBarberNotifier = shop->getBarberSemaphore();
    mCustomersNotifier = shop->getCustomersSemaphore();

    mBarberThread = std::thread(operating, this);
}

void Barber::cutHair()
{
    std::cout << "Barber : cutHair()\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
}

void Barber::operating()
{
    while (mAlive)
    {
        mCustomersNotifier->Wait();
        pBelongsToShop->removeWaitingCustomer();
        mBarberNotifier->Signal();
        cutHair();
    }
}

void Barber::terminate()
{
    mAlive = false;
}

void Barber::joinThread()
{
    mBarberThread.join();
}
