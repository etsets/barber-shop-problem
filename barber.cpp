#include "barber.h"
#include "shop.h"
#include "customer.h"

#include <iostream>
#include <chrono>


Barber::Barber(Shop* shop)
    :mBarberThread(nullptr)
{
    std::cout << "Barber : constructor \n";

    pBelongsToShop = shop;
    mBarberNotifier = pBelongsToShop->getBarberSemaphore();
    mCustomersNotifier = pBelongsToShop->getCustomersSemaphore();
}

void Barber::start()
{
    mBarberThread.reset(new std::thread(&Barber::operating, this));
}

void Barber::cutHair(Customer* c)
{
    std::cout << "Barber : cutHair(" << c->getCustomerName() << ") \n";
    //std::this_thread::sleep_for(std::chrono::seconds(4));
}

void Barber::operating()
{
    for (;;)
    {
        mCustomersNotifier->Wait();
        Customer* c = pBelongsToShop->removeWaitingCustomer();

        //In case of null customer, the shop has closed, so barber terminates
        if (c == nullptr)
        {
            break;
        }
        cutHair(c);
        mBarberNotifier->Signal();
    }
}

void Barber::joinThread()
{
    mBarberThread->join();
}

