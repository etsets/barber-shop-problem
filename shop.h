#ifndef SHOP_H
#define SHOP_H

#include "semaphore.h"
#include "barber.h"
#include "customer.h"

#include <iostream>
#include <vector>

class Shop
{
public:
    Shop(int numberOfChairs);
    ~Shop();
    void stop();
    bool takeSeat(Customer *c);

    Customer* removeWaitingCustomer();

    Semaphore* getBarberSemaphore() { return &mBarberSemaphore; }
    Semaphore* getCustomersSemaphore() { return &mCustomersSemaphore; }

private:
    int mMaxChairs;
    int mWaitingCustomers;

    Barber *mTheBarber;
    std::vector<Customer*> mTheCustomers;

    // Synchronization objects
    Semaphore mBarberSemaphore;
    Semaphore mCustomersSemaphore;

    std::mutex mShopMutex;
};

#endif // SHOP_H
