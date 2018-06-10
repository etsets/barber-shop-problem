#ifndef SEMAPHORE_H
#define SEMAPHORE_H

using namespace std;
#include <mutex>
#include <atomic>
#include <condition_variable>

class Semaphore
{
public:
    Semaphore(int initialValue);

    void Signal();       // Increment
    void Wait();         // Decrement

private:
    std::atomic<int> mSemaphoreValue;
    std::mutex mMutexObject;
    std::condition_variable mConditionVariable;
};


#endif // SEMAPHORE_H
