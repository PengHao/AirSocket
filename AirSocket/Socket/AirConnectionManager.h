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
#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif // WIN32
#include <map>
#include <vector>
#include <exception>
#include "Thread/AirThread.h"
#include "AirConnection.h"
#include "AirConnectionManagerDelegate.h"

namespace AirCpp {
    class ConnectionIOFactory;
    class ConnectionManager {
    protected:
        
        std::map<int, Connection *> m_mapConnections;
        std::list<int> m_ListWillTimeoutConnections;
        
        struct timeval mTimeout;
        struct timeval mDefaultTimeOut;
        
        bool m_bActivate;
        
        fd_set m_ConnSet;
        pthread_cond_t p_cond;
        Thread *m_pThread;
        
        int m_iMaxHandle;
        
        ConnectionManagerDelegate *m_pConnectionObserver;
        
        ConnectionIOFactory *m_pConnectionIOFactory;
        
        ConnectionManager(ConnectionManagerDelegate *pConnectionObserver, ConnectionIOFactory *pConnectionIOFactory);
        
        void resetTimeOut();
        
        void selectTimeOut();
        
        void selectError();
        
        void selectRead();
        
        void select();
        
        virtual ~ConnectionManager();
    public:
        static ConnectionManager *create(ConnectionManagerDelegate *pConnectionObserver, ConnectionIOFactory *pConnectionIOFactory);
        
        Connection * create(const std::string &host, int port, int domainType = AF_INET, int dataType = SOCK_STREAM, int protocol = IPPROTO_TCP);
        
        Connection * create(Socket *ps);
        
        void destroyConnection(const Connection* connection);
        
        void terminate(bool needCallBack = false);
        
    };
}
#endif /* AirClient_h */
