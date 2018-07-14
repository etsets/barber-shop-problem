#ifndef BARBER_H
#define BARBER_H

#include <thread>
#include <future>
#include <memory>

class Shop;
class Semaphore;

class Barber
{
public:
    Barber(Shop* shop);
    void joinThread();
    void stop();
    void start();
    void setShop(Shop* shop) { pBelongsToShop = shop; }
private:
    std::unique_ptr<std::thread> mBarberThread;

    std::promise<void> exitSignal;
    std::future<void> futureObj;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    void operating();
    void cutHair();
    bool stopRequested();
};

#endif // BARBER_H
