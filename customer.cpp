#include "customer.h"
#include "shop.h"
#include <iostream>
#include <chrono>

Customer::Customer(std::string name, Shop* shop)
    :futureObj(exitSignal.get_future())
    ,mCustomerName(name)
    ,pBelongsToShop(shop)
    ,mTerminated(false)
{
    std::cout << "\n\nCustomer : " << mCustomerName << " - ctor \n";
    mCustomerThread = std::thread(operating, this);
}

void Customer::operating()
{
    while (!stopRequested())
    {
        if (!pBelongsToShop->emptySeatsExist())
        {
            balk();
            mTerminated = true;
            break;
        }

        pBelongsToShop->addWaitingCustomer();
        std::cout << "Customer : - operating... Before signal \n";
        pBelongsToShop->getCustomersSemaphore()->Signal();
        pBelongsToShop->getBarberSemaphore()->Wait();
        getHaircut();
        mTerminated = true;
        break;
    }
}

void Customer::getHaircut()
{
    std::cout << "Customer : " << mCustomerName << " - getHaircut()\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Customer::balk()
{
    std::cout << "Customer : " << mCustomerName << " - balk()\n";
}

void Customer::joinThread()
{
    mCustomerThread.join();
}

//Checks if thread is requested to stop
bool Customer::stopRequested()
{
    // checks if value in future object is available
    if (futureObj.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
        return false;
    return true;
}
// Request the thread to stop by setting value in promise object
void Customer::stop()
{
    exitSignal.set_value();
}

