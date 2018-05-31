#include "barber.h"

Barber::Barber()
{
    mBarberThread = std::thread(operating, this);
    mIsBusy = false;
}

void Barber::cutHair()
{

}

void Barber::operating()
{

}
