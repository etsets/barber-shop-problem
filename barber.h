#ifndef BARBER_H
#define BARBER_H

#include <thread>
#include <mutex>

class Barber
{
public:
    Barber();
    void cutHair();
    bool IsBarberBusy() { return mIsBusy; }
    void operating();

private:
    bool mIsBusy;
    std::thread mBarberThread;
};

#endif // BARBER_H
