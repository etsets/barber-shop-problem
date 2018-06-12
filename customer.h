#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <thread>

class Shop;
class Semaphore;

class Customer
{
public:
    Customer(std::string name, Shop* shop);
    void joinThread();

private:
    std::string mCustomerName;
    std::thread mCustomerThread;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    void operating();
    void getHaircut();  // Customer is served and occupies the chair
    void balk();        // Leave if no chair empty
};

#endif // CUSTOMER_H
