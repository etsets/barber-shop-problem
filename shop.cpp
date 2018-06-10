#include "shop.h"


Shop::Shop(int mMaxChairs)
    :mMaxChairs(mMaxChairs)
{
    mBarberSemaphore = new Semaphore(1);
    mCustomersSemaphore = new Semaphore(0);
    mTheBarber = new Barber(this, mBarberSemaphore, mCustomersSemaphore);
}

Shop::~Shop()
{
    if (mTheBarber != nullptr)
    {
        delete mTheBarber;
    }

    if (mBarberSemaphore != nullptr)
    {
        delete mBarberSemaphore;
    }

    if (mCustomersSemaphore != nullptr)
    {
        delete mCustomersSemaphore;
    }
}

void Shop::newCustomerArrives(std::string customerName)
{
    mShopMutex.lock();
    mTheCustomers.emplace_back(new Customer(customerName, this, mBarberSemaphore, mCustomersSemaphore));
    mShopMutex.unlock();
}

bool Shop::emptySeatsExist()
{
    mShopMutex.lock();
    bool returnValue = (mWaitingCustomers < mMaxChairs);
    mShopMutex.unlock();

    return returnValue;
}

void Shop::addWaitingCustomer()
{
    mShopMutex.lock();
    mWaitingCustomers++;
    mShopMutex.unlock();
}

void Shop::removeWaitingCustomer()
{
    mShopMutex.lock();
    mWaitingCustomers--;
    mShopMutex.unlock();
}

