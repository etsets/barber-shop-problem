#include "shop.h"


Shop::Shop(int mMaxChairs)
    :mMaxChairs(mMaxChairs)
{
    mBarberSemaphore = new Semaphore(1);
    mCustomersSemaphore = new Semaphore(0);
    mTheBarber = new Barber(this);
}

Shop::~Shop()
{
    delete mTheBarber;
    delete mBarberSemaphore;
    delete mCustomersSemaphore;
}

void Shop::newCustomerArrives(std::string customerName)
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    mTheCustomers.emplace_back(new Customer(customerName, this));
}

bool Shop::emptySeatsExist()
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    return (mWaitingCustomers < mMaxChairs);
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
}

void Shop::joinThreads()
{
    mTheBarber->joinThread();
    for(const auto &it : mTheCustomers)
    {
        it->joinThread();
    }
}

