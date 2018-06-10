#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <thread>

using namespace std;

class Shop;
class Semaphore;

class Customer
{
public:
    Customer(std::string name, Shop* shop, Semaphore* barberNotifier, Semaphore* customersNotifier);
    ~Customer();
    void operating();

private:
    std::string mCustomerName;
    std::thread mCustomerThread;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    void getHaircut();  // Customer is served and occupies the chair
    void balk();        // Leave if no chair empty
};

#endif // CUSTOMER_H
