#include "semaphore.h"


Semaphore::Semaphore(int initialValue)
    :mSemaphoreValue(initialValue)
{

}

void Semaphore::Increment() //Signal - Unlock
{
    mSemaphoreValue++;
    mMutexObject.unlock();
}

void Semaphore::Decrement() //Wait - Lock
{
    mSemaphoreValue--;
    if (mSemaphoreValue < 0)
    {
        mMutexObject.lock();
    }
}
