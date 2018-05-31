#ifndef SHOP_H
#define SHOP_H

#include "barber.h"
#include "customer.h"
#include <thread>
#include <vector>

class Shop
{
public:
    Shop(int numberOfChairs);
    void setNewCustomer(std::string customerName);

private:
    int mMaxChairs;
    Barber mBarber;
    std::vector<Customer> mWaitingCustomers;

};

#endif // SHOP_H
