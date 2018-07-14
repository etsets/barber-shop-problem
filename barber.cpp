#include "barber.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Barber::Barber(Shop* shop)
    :mBarberThread(nullptr)
    ,futureObj(exitSignal.get_future())
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

void Barber::cutHair()
{
    std::cout << "Barber : cutHair()\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
}

void Barber::operating()
{
    while (stopRequested() == false)
    {
        mCustomersNotifier->Wait();
        pBelongsToShop->removeWaitingCustomer();
        mBarberNotifier->Signal();
        cutHair();
    }
}

void Barber::joinThread()
{
    mBarberThread->join();
}

//Checks if thread is requested to stop
bool Barber::stopRequested()
{
    // checks if value in future object is available
    if (futureObj.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
        return false;
    return true;
}
// Request the thread to stop by setting value in promise object
void Barber::stop()
{
    exitSignal.set_value();
}
