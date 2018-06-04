#ifndef BARBER_H
#define BARBER_H

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Shop;

class Barber
{
public:
    Barber(Shop* shop);
    void terminate();

private:
    std::thread mBarberThread;
    bool mAlive;
    Shop* pBelongsToShop;

    void cutHair();
    void operating();
};

#endif // BARBER_H
