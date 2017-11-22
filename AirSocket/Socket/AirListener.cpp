//
//  AirListener.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include "AirListener.h"
namespace AirCpp{
    
    Listener::Listener(int iDomainType, int iDataType, int iProtocol):
    m_iDomainType(iDomainType),
    m_iDataType(iDataType),
    m_iProtocol(iProtocol),
    m_ulCurrentConnectionNum(0),
    m_ulMaxConnectionNum(100),
    bStarting(false),
    m_uiMaxNumInQueue(10)
    {
    }
    
    /**
     usPortnum, 一个监听的接口.
     uiBacklog, 一个决定监听队列大小的整数，当有一个连接请求到来，就会进入此监听队列，当队列满后，新的连接请求会返回错误。
     */
    int Listener::init(unsigned short usPortnum, unsigned int uiBacklog) {
        if (mSocket.init(m_iDomainType, m_iDataType, m_iProtocol) == 0 && mSocket.bind(usPortnum) == 0 && mSocket.listen(uiBacklog) == 0) {
            return 0;
        } else {
            return -1;
        }
    }
    
    
    int Listener::startListen(ListenerCallBack callback){
        printf("start listen socketHandle\n");
        bStarting = true;
        int  t = -1;
        sockaddr clientAddr;
        socklen_t clientSize;
        while (bStarting) {
            t = mSocket.accept(&clientAddr, &clientSize);
            if (t < 0) { /* get a connection */
                if (errno == EINTR)             /* EINTR might happen on accept(), */
                {
                    sleep(1.0);
                    continue;                   /* try again */
                }
                else
                    return -1;
            } else {
                Socket *pSocket = new Socket();
                pSocket->init(t, &clientAddr, &clientSize);
                Connection *pConnect = new Connection(pSocket);
                callback(pConnect);
            }
            sleep(1.0);
        }
        return 0;
    };
    
    void Listener::stopListen(){
        bStarting = false;
        mSocket.close();
    }
    
}
