#ifndef SHOP_H
#define SHOP_H

using namespace std;

#include <iostream>
#include <map>
#include <mutex>
#include "semaphore.h"
#include "barber.h"
#include "customer.h"

class Shop
{
public:
    Shop(int numberOfChairs);
    void newCustomer(std::string customerName);
    void cleanupCustomerGarbage(std::string customerName);

private:
    int mMaxChairs;
    Barber mTheBarber;
    int mWaitingCustomers;
    std::map<std::string, Customer> mTheCustomers;

    // Synchronization objects
    Semaphore mBarberSemaphore;
    Semaphore mCustomersSemaphore;
    std::mutex mWaitingCustomersMutex;
    std::mutex mCustomersMapMutex;
};

#endif // SHOP_H
