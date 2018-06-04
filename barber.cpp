#include "barber.h"
#include "shop.h"

Barber::Barber(Shop* shop)
    :mAlive(true)
    ,pBelongsToShop(shop)
{
    mBarberThread = std::thread(operating, this);
    mBarberThread.join();
}

void Barber::cutHair()
{
    std::cout << "Barber : cutHair()\n";
}

void Barber::operating()
{
    while (mAlive)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Barber::terminate()
{
    mAlive = false;
}
