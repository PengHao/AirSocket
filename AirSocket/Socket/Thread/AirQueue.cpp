//
//  AirQueue.cpp
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#include "AirQueue.h"
#include <signal.h>
#ifdef WIN32
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#include <io.h>  
#include <process.h>  
#include <windows.h>
#include <ws2tcpip.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif // WIN32

namespace AirCpp {
    void Queue::clean() {
        mLock.lock();
        m_listOperations.clear();
        mLock.unlock();
    }
    
    void Queue::pushOperation(Operation *operation){
        mLock.lock();
        m_listOperations.push_back(operation);
        mLock.unlock();
    }
    
    const Operation *Queue::popfront_operation() {
        if (m_listOperations.size() == 0) {
            return nullptr;
        }
        if (mLock.try_lock() != 0) {
            return nullptr;
        }
        const Operation * rs = m_listOperations.front();
        m_listOperations.pop_front();
        mLock.unlock();
        return rs;
    }
    
    Queue::Queue(){
        mLock.init(LOCK_TYPE_NORMAL);
        m_listOperations.clear();
    };
    
    Queue::~Queue(){
    };
}
