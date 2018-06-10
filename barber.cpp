#include "barber.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Barber::Barber(Shop* shop, Semaphore* barberNotifier, Semaphore* customersNotifier)
    :mAlive(true)
    ,pBelongsToShop(shop)
    ,mBarberNotifier(barberNotifier)
    ,mCustomersNotifier(customersNotifier)
{
    mBarberThread = std::thread(operating, this);
    mBarberThread.join();
}

Barber::~Barber()
{

}

void Barber::cutHair()
{
    std::cout << "Barber : cutHair()\n";
}

void Barber::operating()
{
    while (mAlive)
    {
        mCustomersNotifier->Wait();
        pBelongsToShop->removeWaitingCustomer();
        mBarberNotifier->Signal();
        cutHair();
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }
}

void Barber::terminate()
{
    mAlive = false;
}
