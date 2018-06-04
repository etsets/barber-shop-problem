#include "shop.h"


Shop::Shop(int mMaxChairs)
    :mMaxChairs(mMaxChairs)
    ,mTheBarber(this)
    ,mBarberSemaphore(0)
    ,mCustomersSemaphore(0)
{

}

void Shop::newCustomer(std::string customerName)
{
    mCustomersMapMutex.lock();
    mTheCustomers.emplace(customerName, Customer(customerName, this));
    mCustomersMapMutex.unlock();
}

void Shop::cleanupCustomerGarbage(std::string customerName)
{
    mCustomersMapMutex.lock();
    mTheCustomers.erase(customerName);
    mCustomersMapMutex.unlock();
}

