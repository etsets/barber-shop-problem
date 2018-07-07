#include "shop.h"
#include <chrono>

Shop::Shop(int mMaxChairs)
    :mMaxChairs(mMaxChairs)
    ,mBarberSemaphore(1, "Barber Semaphore")
    ,mCustomersSemaphore(0, "Customer Semaphore")
{
    std::cout << "Shop : - ctor \n";
    mWaitingCustomers = 0;
    mTheBarber.setShop(this);
}

Shop::~Shop()
{
    mTheCustomers.clear();
}

void Shop::newCustomerArrives(Customer *newCustomer)
{
    std::cout << "Shop : - newCustomerArrives()\n";
    std::lock_guard<std::mutex> lock(mShopMutex);
    mTheCustomers.emplace_back(newCustomer);
}

bool Shop::emptySeatsExist()
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    std::cout << "Shop : - emptySeatsExist() - mWaitingCustomers: " << mWaitingCustomers << " mMaxChairs : " << mMaxChairs << "\n";

    return ((mWaitingCustomers < mMaxChairs));
}

void Shop::addWaitingCustomer()
{
    std::lock_guard<std::mutex> lock(mShopMutex);

    mWaitingCustomers++;
    std::cout << "Shop : - addWaitingCustomer()" << mWaitingCustomers << "\n";
}

void Shop::removeWaitingCustomer()
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    mWaitingCustomers--;
    clearFirstTerminatedCustomerFound();
}

void Shop::clearFirstTerminatedCustomerFound()
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    // Check if there exist any Customers have been finished
    // and delete the first found
    auto it = mTheCustomers.begin();
    for (;it != mTheCustomers.end(); ++it)
    {
        if ((*it)->isTerminated())
        {
            break;
        }
    }

    (*it)->joinThread();
    mTheCustomers.erase(it);
}

void Shop::stop()
{
    mTheBarber.stop();
    mTheBarber.joinThread();

    //Stop any remaining Customer threads
    std::lock_guard<std::mutex> lock(mShopMutex);
    for (auto &it : mTheCustomers)
    {
        it->stop();
        it->joinThread();
    }
}

