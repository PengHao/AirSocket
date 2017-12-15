//
//  Connection.h
//  AirCpp
//
//  Created by Penghao on 14-2-25.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirBSDSocketIO__
#define __AirCpp__AirBSDSocketIO__

#include <iostream>
#include "AirSocket.h"
#include "AirSocketConfig.h"
#include "AirFormatDataIO.h"
#include "Thread/AirThreadLock.h"


namespace AirCpp{
#define TEMP_BUFFER_SIZE 1024
    typedef enum {
        CONNECTED = 1,  //connected: connected
        RECONNECTING = 2,   //reconnecting: will be reconnect
        DISCONNECTED = 3,   //disconnect: will be destroy
    } Status;
    
    
    class ConnectionManager;
    class Listener;
    class Server;
    class ConnectionManagerDelegate;
    class Session;
    class FormatDataIO;
    class Connection {
        friend Session;
        friend ConnectionManager;
    protected:
        Socket *m_pSocket;
        int m_iDomainType;
        int m_iDataType;
        int m_iProtocol;
        int m_iPort;
        std::string m_strHost;
        FormatDataIO *m_pConnectionIO;
        Lock *m_pReadLock;
        Lock *m_pWriteLock;
        Status m_status;
    protected:
        
        Connection(int domainType, int dataType, int protocol, ConnectionManagerDelegate * pConnectionObserver, FormatDataIO *pConnectionIO);
        
        Connection(Socket *ps, ConnectionManagerDelegate * pConnectionObserver, FormatDataIO *pConnectionIO);
        
        int init(const std::string &host, int port);
        
        ~Connection();
    public:
        
        Status getStatus();
        
        void setStatus(Status status);
        
        int reconnect();
        
        int getHandle() const ;
        
        bool send(const FormatedData *package) const ;
        
        bool read(ReseivePackageHandler reseiveHandler) const ;
        
    };
}

#endif /* defined(__AirCpp__Connection__) */
