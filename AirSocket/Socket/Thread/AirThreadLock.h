//
//  AirThreadLock.h
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#ifndef AirThreadLock_h
#define AirThreadLock_h

#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <sys/types.h>
#include <pthread.h>



namespace AirCpp {
    
    typedef enum {
        LOCK_TYPE_NORMAL = PTHREAD_MUTEX_NORMAL,            //普通
        LOCK_TYPE_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK,    //即纠错锁
        LOCK_TYPE_RECURSIVE = PTHREAD_MUTEX_RECURSIVE,      //互斥锁
    } LockType;
    
    class Lock{
    protected:
        
        pthread_mutex_t mutex;
    public:
        
        int init(LockType lockType);
        
        int lock();
        
        int unlock();
        
        int try_lock();
        
        int try_destroy();
    };
    
    
    class Semaphore{
    protected:
        sem_t thread_sem;
    public:
        int init(bool shared);
        
        int wait();
        
        int post();
        
        int destroy();
        
        ~Semaphore();
    };
    
    
    class RWLock{
    protected:
        pthread_rwlock_t rwlock;
    public:
        int init();
        
        int rdlock();
        
        int wrlock();
        
        int try_rdlock();
        
        int try_wrlock();
        
        int unlock();
        
        int destroy();
    };
}
#endif /* AirThreadLock_h */
