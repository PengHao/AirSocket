//
//  AirBSDServer.cpp
//  Socket
//
//  Created by 彭浩 on 16/4/28.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#include "AirServer.h"
#include "AirSocket.h"
#include "AirSocketDefine.h"
namespace AirCpp {
    Server::~Server() {
        if (m_pListenThread) {
            delete m_pListenThread;
        }
    }
    
    int Server::startListen(){
        if (mSocket.init(AF_INET, SOCK_STREAM, IPPROTO_TCP) != 0
            || mSocket.bind(m_uiPort) != 0
            || mSocket.listen(m_uiBackLog) != 0) {
            perror("listen port failed!");
            return -1;
        }
        
        LOG_INFO("start listen socketHandle\n");
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
                Connection *pConnection = m_pConnectionManager->create(pSocket);
                LOG_INFO("handle connection\r\n");
                if (mHandle) {
                    mHandle(pConnection);
                }
            }
            sleep(1.0);
        }
        return 0;
    };
    
    void Server::stopListen(){
        bStarting = false;
        mSocket.close();
    }
    
    Server::Server(unsigned short usPort, unsigned int uiBacklog):
    m_uiPort(usPort),
    m_uiBackLog(uiBacklog),
    mHandle(nullptr){
        m_pListenThread = new Thread();
        m_pListenThread->init();
    }
    
    Server *Server::Create(unsigned short usPort, unsigned int uiBacklog, ConnectionManager *pConnectionManager) {
        Server *server = new Server(usPort, uiBacklog);
        server->m_pConnectionManager = pConnectionManager;
        return server;
    }
    
    void Server::run(OnHandleConnection handle) {
        mHandle = handle;
        startListen();
    }
}
