#ifndef SHOP_H
#define SHOP_H

#include "semaphore.h"
#include "barber.h"
#include "customer.h"

#include <iostream>
#include <list>

class Shop
{
public:
    Shop(int numberOfChairs);
    ~Shop();
    void newCustomerArrives(std::string customerName);
    bool emptySeatsExist();
    void addWaitingCustomer();
    void removeWaitingCustomer();
    void joinThreads();
    Semaphore* getBarberSemaphore() { return &mBarberSemaphore; }
    Semaphore* getCustomersSemaphore() { return &mCustomersSemaphore; }

private:
    int mMaxChairs;
    int mWaitingCustomers;

    Barber *mTheBarber;
    std::list<Customer*> mTheCustomers;

    // Synchronization objects
    Semaphore mBarberSemaphore;
    Semaphore mCustomersSemaphore;

    std::mutex mShopMutex;
};

#endif // SHOP_H
