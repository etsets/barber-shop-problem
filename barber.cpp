#include "barber.h"
#include "shop.h"

Barber::Barber(Shop* shop)
    :mAlive(true)
    ,pBelongsToShop(shop)
{
    // EVA: This does not compile. I would propose to allow the user of this class to have more granular control over the
    // thread creation and termination. As it is, this constructor will lock until some other thread terminates the barber.
    // But I would argue that it is not a good practice to have a constructor lock forever and use an object whose constructor never
    // completed. Imagine that you make a class LicencedBarber: public Barber. How can LicencedBarber contructor run if the Barber
    // constructor blocks forever?

    // mBarberThread = std::thread(operating, this);
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
        // EVA: If there is work to do, or you need to quit, is there any way to wake up immediately and not have to wait for 1 sec to pass?
        // On the other hand, if there is nothing to do, is there any way to avoid waking up every second for no reason?
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Barber::terminate()
{
    // EVA: How many threads access this variable? Is it's usage safe?
    mAlive = false;
}
