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
    ~Customer();
    const std::string &getCustomerName() const { return mCustomerName; }
    void start();

private:
    std::string mCustomerName;
    Shop* pBelongsToShop;
    std::unique_ptr<std::thread> mCustomerThread;

    void operating();
    void getHaircut();  // Customer is served and occupies the chair
    void balk();        // Leave if no chair empty
};

#endif // CUSTOMER_H
