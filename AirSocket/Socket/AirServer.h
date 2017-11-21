//
//  Server.h
//  Socket
//
//  Created by 彭浩 on 16/4/28.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#ifndef Server_h
#define Server_h

#include <stdio.h>
#include <map>
#include <vector>
#include "AirListener.h"
#include "Thread/AirThread.h"
#include "Thread/AirOperation.h"
#include "AirConnectionObserverCenter.h"
#include "AirSession.h"

namespace AirCpp {
    
    class Server {
    protected:
        Listener *_pListener;
        Thread *m_pListenThread;
        unsigned short m_uiPort;
        unsigned int m_uiBackLog;
        std::map<int, Connection *> m_mapConnections;
        fd_set m_ConnSet;
        ConnectionObserverCenter *m_pConnectionObserverCenter;
        SessionObserver *m_pSessionObserver;
        ~Server();
        
        void startListen();
        Server(unsigned short usPort, unsigned int uiBacklog);
    public:
        static Server *Create(unsigned short usPort, unsigned int uiBacklog, SessionObserver *pSessionObserver);
        
        void run();
    };
}

#endif /* AirBSDServer_h */
