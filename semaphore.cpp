#include "semaphore.h"
#include <cassert>
#include <iostream>

Semaphore::Semaphore(int initialValue, std::string id)
    //:mSemaphoreValue(initialValue)
    //,mId(id)
{
    mSemaphoreValue = initialValue;
    mId = id;
    std::cout << "Semaphore  " << mId << " : - ctor - initialValue:" << initialValue << " \n";
    assert(initialValue >= 0);
}

void Semaphore::Signal() //Signal - Unlock
{
    std::lock_guard<std::mutex> lck(mMutexObject);
    mSemaphoreValue++;
    //std::cout << "Semaphore " << mId << " : - Signal - initialValue:" << mSemaphoreValue << " \n";
    if (mSemaphoreValue == 1)
    {
        mConditionVariable.notify_one();
    }
}

void Semaphore::Wait() //Wait - Lock
{
    std::unique_lock<std::mutex> lck(mMutexObject);
    //std::cout << "Semaphore " << mId << " :- Wait - initialValue:" << mSemaphoreValue << " \n";
    while (mSemaphoreValue <= 0)
    {
        mConditionVariable.wait(lck);
    }

    mSemaphoreValue--;
    assert(mSemaphoreValue >= 0);
}
