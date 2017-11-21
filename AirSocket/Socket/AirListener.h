//
//  Listener.h
//  AirCpp
//
//  Created by Penghao on 14-2-25.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__Listener__
#define __AirCpp__Listener__

#include <iostream>
#include <map>
#include "AirConnection.h"

namespace AirCpp{
    typedef std::function< void(Connection *connect)> ListenerCallBack;
    class Listener {
    protected:
        unsigned int m_uiMaxNumInQueue;
        unsigned long m_ulMaxConnectionNum;
        unsigned long m_ulCurrentConnectionNum;
        bool bStarting;
        Socket mSocket;
        int m_iDomainType;
        int m_iDataType;
        int m_iProtocol;
    public:
        
        
        Listener(int iDomainType, int iDataType, int iProtocol);
        
        /**
         usPortnum, 一个监听的接口.
         uiBacklog, 一个决定监听队列大小的整数，当有一个连接请求到来，就会进入此监听队列，当队列满后，新的连接请求会返回错误。
         */
        int init(unsigned short usPortnum, unsigned int uiBacklog);
        
        
        int startListen(ListenerCallBack callback);
        
        void stopListen();
    };
}

#endif /* defined(__AirCpp__Listener__) */
