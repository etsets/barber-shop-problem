#include "semaphore.h"

Semaphore::Semaphore(int initialValue)
    :mSemaphoreValue(initialValue)
{
}

void Semaphore::Signal() //Signal - Unlock
{
    mSemaphoreValue++;
    mConditionVariable.notify_all();
}

void Semaphore::Wait() //Wait - Lock
{
    mSemaphoreValue--;
    if (mSemaphoreValue >= 0)
    {
        return;
    }

    std::unique_lock<std::mutex> lck(mMutexObject);
    mConditionVariable.wait(lck);
}
