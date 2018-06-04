#ifndef SEMAPHORE_H
#define SEMAPHORE_H

using namespace std;
#include <mutex>

class Semaphore
{
public:
    Semaphore(int initialValue);

    void Increment();       // Signal()
    void Decrement();       // Wait()

private:
    int mSemaphoreValue;
    std::mutex mMutexObject;
};


#endif // SEMAPHORE_H
