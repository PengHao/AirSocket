//
//  AirQueue.cpp
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#include "AirQueue.h"
#include <pthread/pthread.h>
#include<unistd.h>
#include <signal.h>

namespace AirCpp {
    
    void Queue::pushOperation(Operation *operation){
        m_listOperations.push_back(operation);
    }
    
    
    const Operation *Queue::head_operation() {
        return *m_listOperations.begin();
    }
    
    void Queue::remove_operation(const Operation *o) {
        m_listOperations.remove(o);
    }
    
    Queue::Queue(){
        
    };
    
    Queue::~Queue(){
    };
}
