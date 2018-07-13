#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <atomic>
#include <condition_variable>

class Semaphore
{
public:
    Semaphore(int initialValue, std::string id);

    void Signal();       // Increment
    void Wait();         // Decrement

private:
    std::atomic<int> mSemaphoreValue;
    std::mutex mMutexObject;
    std::condition_variable mConditionVariable;
    std::string mId;
};


#endif // SEMAPHORE_H
