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

namespace AirCpp{
#define TEMP_BUFFER_SIZE 1024
    class ConnectionManager;
    class Listener;
    class Server;
    class ConnectionObserver;
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
        ConnectionObserver *m_pConnectionObserver;
        FormatDataIO *m_pConnectionIO;
    protected:
        
        Connection(int domainType, int dataType, int protocol, ConnectionObserver * pConnectionObserver, FormatDataIO *pConnectionIO);
        
        Connection(Socket *ps, ConnectionObserver * pConnectionObserver, FormatDataIO *pConnectionIO);
        
        int init(const std::string &host, int port);
        
        void onTimeOut();
        
        void onReadable();
        
        long long read(char *c_data, long long length) const ;
        
        long long send(const char *c_data, long long length) const ;
        
    public:
        ~Connection();
        
        int getHandle() const ;
        
        bool send(const FormatedData *package) const ;
        
        bool read(ReseivePackageHandler reseiveHandler) const ;
        
    };
}

#endif /* defined(__AirCpp__Connection__) */
