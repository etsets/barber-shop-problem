#ifndef SHOP_H
#define SHOP_H

/// EVA: Never do this in a header in production code. You are spewing all the contents of std to
/// any file that includes the header, that is guaranteed to cause chaos.
/// Additionally, the namespace std does not exist here, since no headers from the std lib have been included
/// in these first few lines of the file.
using namespace std;

/// EVA: Always include system headers after any project specific ones.
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
    /// EVA: Does the shop need to "own" the customers? Do you need a map? Do you need O(logN) access to the customers by name?
    ///  Do the customers need names?. I think a simple int identifier for each customer should suffice.
    std::map<std::string, Customer> mTheCustomers;

    // Synchronization objects
    Semaphore mBarberSemaphore;
    Semaphore mCustomersSemaphore;
    std::mutex mWaitingCustomersMutex;
    std::mutex mCustomersMapMutex;
};

#endif // SHOP_H
