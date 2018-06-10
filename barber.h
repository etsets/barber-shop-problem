#ifndef BARBER_H
#define BARBER_H

#include <thread>

using namespace std;

class Shop;
class Semaphore;

class Barber
{
public:
    Barber(Shop* shop, Semaphore* barberNotifier, Semaphore* customersNotifier);
    ~Barber();
    void terminate();
    void operating();

private:
    std::thread mBarberThread;
    bool mAlive;

    Shop* pBelongsToShop;
    Semaphore* mBarberNotifier;
    Semaphore* mCustomersNotifier;

    void cutHair();

};

#endif // BARBER_H
