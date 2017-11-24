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

#include "Thread/AirThread.h"
#include "Thread/AirOperation.h"
#include "AirConnectionManager.h"
namespace AirCpp {
    class Connection;
    typedef std::function<void(const Connection *)> OnHandleConnection;
    class Server {
    protected:
        Thread *m_pListenThread;
        unsigned short m_uiPort;
        unsigned int m_uiBackLog;
        std::map<int, Connection *> m_mapConnections;
        ConnectionManager *m_pConnectionManager;
        Socket mSocket;
        
        unsigned int m_uiMaxNumInQueue;
        unsigned long m_ulMaxConnectionNum;
        unsigned long m_ulCurrentConnectionNum;
        bool bStarting;
        OnHandleConnection mHandle;
        
        fd_set m_ConnSet;
        ~Server();
        
        int startListen();
        Server(unsigned short usPort, unsigned int uiBacklog);
        void stopListen();
        
    public:
        static Server *Create(unsigned short usPort, unsigned int uiBacklog, ConnectionManager *pConnectionManager);
        
        void run(OnHandleConnection handle);
    };
}

#endif /* AirBSDServer_h */
