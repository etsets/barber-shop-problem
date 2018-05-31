#include "customer.h"

Customer::Customer(std::string name)
    :mCustomerName(name)
    ,mIsServed(false)
{
    mCustomerThread = std::thread(operating, this);
}

void Customer::operating()
{
    while(!mIsServed)
    {
        //wait... sleep
    }
}

void Customer::getHaircut()
{

}

void Customer::balk()
{
    mCustomerThread.join();
}
