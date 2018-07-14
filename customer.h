#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <thread>
#include <future>

class Shop;
class Semaphore;

class Customer
{
public:
    Customer(std::string name, Shop* shop);
    bool isTerminated() const { return mTerminated; }
    const std::string &getCustomerName() const { return mCustomerName; }
private:
    std::string mCustomerName;
    Shop* pBelongsToShop;
    std::atomic<bool> mTerminated;

    void operating();
    void getHaircut();  // Customer is served and occupies the chair
    void balk();        // Leave if no chair empty
};

#endif // CUSTOMER_H
