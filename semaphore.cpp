#include "semaphore.h"


Semaphore::Semaphore(int initialValue)
    :mSemaphoreValue(initialValue)
{

}

void Semaphore::Increment() //Signal - Unlock
{
    // EVA: If more than one thread calls this function at the same time, is it guaranteed that
    // mSemaphoreValue will be incremented exactly once by each thread and end-up to have the correct value finally?
    mSemaphoreValue++;

    // Is it guaranteed that the mutex was locked before getting unlocked here?
    // If it was locked, is it guaranteed that the thread that locked it is the same thread that is unlocking it?
    // See: http://www.cplusplus.com/reference/mutex/mutex/unlock/
    // "If the mutex is not currently locked by the calling thread, it causes undefined behavior."
    mMutexObject.unlock();

    // Hint: One int and one mutex are insufficient to build a Semaphore. At least one that does a proper wait and not a busy-wait.
}

void Semaphore::Decrement() //Wait - Lock
{
    mSemaphoreValue--;
    /// So if I have 10 threads and make them call "Decrement()" concurrently, will the value become -10?
    /// I don't think a semaphore must ever go into the negatives
    if (mSemaphoreValue < 0)
    {
        mMutexObject.lock();
    }
}
