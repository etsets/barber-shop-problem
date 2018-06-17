#ifndef BARBER_H
#define BARBER_H

#include <thread>
#include <future>

class Shop;
class Semaphore;

class Barber
{
public:
    Barber(Shop* shop);
    void joinThread();
    bool stopRequested();
    void stop();

private:
    std::thread mBarberThread;

    std::promise<void> exitSignal;
    std::future<void> futureObj;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    void operating();
    void cutHair();
};

#endif // BARBER_H
