//
//  AirQueue.h
//  kxmovie
//
//  Created by penghao on 16/1/25.
//
//

#ifndef AirQueue_h
#define AirQueue_h

#include <stdio.h>
#include <functional>
#include <list>
#include "AirOperation.h"
#include "AirThreadLock.h"

#define FINISHED 0x001



namespace AirCpp {
    
    class Queue {
        friend class Thread;
        
    private:
        
        Lock mLock;
        std::list<const Operation *> m_listOperations;
        
        void pushOperation(Operation *operation);
        
    protected:
        
        const Operation *popfront_operation();
        
    public:
        
        void clean();
        
        Queue();
        
        virtual ~Queue();
    };
}

#endif /* AirQueue_h */
