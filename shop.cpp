#include "shop.h"
#include <chrono>
#include <algorithm>

Shop::Shop(int mMaxChairs)
    :mMaxChairs(mMaxChairs)
    ,mBarberSemaphore(1, "Barber Semaphore")
    ,mCustomersSemaphore(0, "Customer Semaphore")
{
    std::cout << "Shop : - ctor \n";
    mWaitingCustomers = 0;
    mTheCustomers.clear();
    mTheBarber = new Barber(this);
    mTheBarber->start();
}

Shop::~Shop()
{
    mTheCustomers.clear();
}

bool Shop::takeSeat(Customer *c)
{
    std::lock_guard<std::mutex> lock(mShopMutex);
    if (mWaitingCustomers >= mMaxChairs)
    {
        return false;
    }

    mTheCustomers.emplace_back(c);
    mWaitingCustomers++;
    return true;
}

Customer* Shop::removeWaitingCustomer()
{
    std::lock_guard<std::mutex> lock(mShopMutex);

    if (mTheCustomers.empty())
    {
        return nullptr;
    }

    Customer *c = mTheCustomers.back();
    mTheCustomers.pop_back();
    mWaitingCustomers--;
    return c;
}

void Shop::stop()
{
    mCustomersSemaphore.Signal(); //Wake up barber in order to terminate its function (is waiting for a customer)
    mTheBarber->joinThread();
}

