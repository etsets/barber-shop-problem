#ifndef BARBER_H
#define BARBER_H

#include <thread>
#include <future>
#include <memory>

class Shop;
class Semaphore;
class Customer;

class Barber
{
public:
    Barber(Shop* shop);
    void joinThread();
    void start();
    void setShop(Shop* shop) { pBelongsToShop = shop; }
private:
    std::unique_ptr<std::thread> mBarberThread;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    void operating();
    void cutHair(Customer *);
};

#endif // BARBER_H
