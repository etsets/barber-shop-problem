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
    void joinThread();
    bool isTerminated() const { return mTerminated; }
    bool stopRequested();
    void stop();

private:
    std::string mCustomerName;
    std::thread mCustomerThread;

    std::promise<void> exitSignal;
    std::future<void> futureObj;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    bool mTerminated;

    void operating();
    void getHaircut();  // Customer is served and occupies the chair
    void balk();        // Leave if no chair empty
};

#endif // CUSTOMER_H
