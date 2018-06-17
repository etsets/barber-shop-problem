#ifndef BARBER_H
#define BARBER_H

#include <thread>
#include <future>

class Shop;
class Semaphore;

class Barber
{
public:
    Barber();
    void joinThread();
    void stop();
    void setShop(Shop* shop) { pBelongsToShop = shop; }
private:
    std::thread mBarberThread;

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
