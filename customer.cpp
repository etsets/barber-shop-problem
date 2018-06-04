#include "customer.h"
#include "shop.h"

Customer::Customer(std::string name, Shop* shop)
    :mCustomerName(name)
    ,pBelongsToShop(shop)
{

    //mCustomerThread = std::thread(operating, this);
    mCustomerThread.join();
}

void Customer::operating()
{
    getHaircut();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Customer::getHaircut()
{
    cout << "Customer : " << mCustomerName << " - getHaircut()\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Customer::balk()
{
    cout << "Customer : " << mCustomerName << " - balk()";
}

