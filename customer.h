#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <thread>
#include <mutex>

using namespace std;

class Customer
{
public:
    Customer(std::string name);

    void getHaircut();  // Customer is served and occupies the chair
    void balk();        // Leave if no chair empty
    void operating();

private:
    std::string mCustomerName;
    std::thread mCustomerThread;
    bool mIsServed;
};

#endif // CUSTOMER_H
