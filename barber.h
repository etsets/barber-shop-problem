#ifndef BARBER_H
#define BARBER_H

#include <thread>

class Shop;
class Semaphore;

class Barber
{
public:
    Barber(Shop* shop);
    void terminate();
    void joinThread();

private:
    std::thread mBarberThread;
    bool mAlive;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    void operating();
    void cutHair();
};

#endif // BARBER_H
