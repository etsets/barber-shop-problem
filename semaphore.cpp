#include "semaphore.h"
#include <cassert>

Semaphore::Semaphore(int initialValue)
    :mSemaphoreValue(initialValue)
{
    assert(initialValue >= 0);
}

void Semaphore::Signal() //Signal - Unlock
{
    std::lock_guard<std::mutex> lck(mMutexObject);
    mSemaphoreValue++;
    if (mSemaphoreValue == 1)
    {
        mConditionVariable.notify_one();
    }
}

void Semaphore::Wait() //Wait - Lock
{
    std::lock_guard<std::mutex> lck(mMutexObject);
    while (mSemaphoreValue < 0)
    {
        mConditionVariable.wait(lck);
    }

    mSemaphoreValue--;
    assert(mSemaphoreValue >= 0);
}
