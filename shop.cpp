#include "shop.h"
#include <chrono>

Shop::Shop(int mMaxChairs)
    :mMaxChairs(mMaxChairs)
    ,mBarberSemaphore(1)
    ,mCustomersSemaphore(0)
{
    mTheBarber = new Barber(this);
}

Shop::~Shop()
{
    delete mTheBarber;
    mTheCustomers.clear();
}

void Shop::newCustomerArrives(Customer *newCustomer)
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    mTheCustomers.emplace_back(newCustomer);
}

bool Shop::emptySeatsExist()
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    return ((mWaitingCustomers < mMaxChairs));
}

void Shop::addWaitingCustomer()
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    mWaitingCustomers++;
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
    // Check if Customers have been finished
    auto it = mTheCustomers.begin();
    Customer* c;
    for (;it != mTheCustomers.end(); ++it)
    {
        if (!((*it)->isTerminated()))
        {
            continue;
        }
        c = (*it);
        break;
    }
    *it = mTheCustomers.back();
    c->joinThread();
    delete c;
}

void Shop::stop()
{
    mTheBarber->stop();
    mTheBarber->joinThread();

    //Stop any remaining Customer threads
    std::lock_guard<std::mutex> lock(mShopMutex);
    for (auto &it : mTheCustomers)
    {
        it->stop();
        it->joinThread();
        delete it;
    }
}

