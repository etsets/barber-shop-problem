#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Shop;

class Customer
{
public:
    Customer(std::string name, Shop* shop);

private:
    std::string mCustomerName;
    std::thread mCustomerThread;
    Shop* pBelongsToShop;

    void operating();
    void getHaircut();  // Customer is served and occupies the chair
    void balk();        // Leave if no chair empty
};

#endif // CUSTOMER_H
