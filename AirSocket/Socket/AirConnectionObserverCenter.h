//
//  AirConnectionObserverCenter.h
//  Socket
//
//  Created by 彭浩 on 16/7/9.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#ifndef AirConnectionObserverCenter_h
#define AirConnectionObserverCenter_h

#include <stdio.h>
#include <sys/time.h>
#include <map>
#include <vector>
#include <exception>
#include "Thread/AirThread.h"
#include "AirConnection.h"
#include "AirConnectionObserver.h"

namespace AirCpp {
    
    class ConnectionObserverCenter {
    protected:
        static ConnectionObserverCenter *_defaultClent;
        std::map<int, Connection *> m_mapConnectionObservers;
        std::list<int> m_ListWillTimeoutConnections;
        
        struct timeval mTimeout;
        struct timeval mDefaultTimeOut;
        
        fd_set m_ConnSet;
        pthread_cond_t p_cond;
        Thread *m_pThread;
        int m_iMaxHandle;
        
        
        ConnectionObserverCenter();
        
        void resetTimeOut();
        
        void onTimeOut();
        
        void onError();
        
        void onRead();
        
        void select();
        
    public:
        static ConnectionObserverCenter *defaultObserverCenter();
        
        bool addObserver(Connection *connection);
        
        ~ConnectionObserverCenter() {
            
        }
        
    };
}
#endif /* AirClient_h */
