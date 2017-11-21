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
#include "AirPackage.h"

namespace AirCpp{
#define TEMP_BUFFER_SIZE 1024
    class ConnectionObserverCenter;
    class Listener;
    class Server;
    class ConnectionObserverCenter;
    
    class Connection {
        friend Listener;
        friend Server;
        friend ConnectionObserverCenter;
    protected:
        Socket *m_pSocket;
        int m_iDomainType;
        int m_iDataType;
        int m_iProtocol;
        
        char m_strTempBuffer[TEMP_BUFFER_SIZE];
    protected:
        
        Connection(int domainType, int dataType, int protocol);
        
        Connection(Socket *ps);
        
        int init(const std::string &host, int port);
        
    public:
        ~Connection();
        
        static Connection * Create(const std::string &host, int port, int domainType = AF_INET, int dataType = SOCK_STREAM, int protocol = IPPROTO_TCP);
        
        int getHandle() const ;
        
        long long read(char *c_data, long long length) const ;
        
        long long send(const char *c_data, long long length) const ;
    };
}

#endif /* defined(__AirCpp__Connection__) */
