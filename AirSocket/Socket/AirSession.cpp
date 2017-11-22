//
//  AirSession.cpp
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/18.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include "AirSession.h"
namespace AirCpp {

    void Session::setUid(long long uid) {
        m_llUid = uid;
    }
    
    Session::Session(Connection *pConnection, SessionObserver *pSessionObserver):
    m_pConnection(pConnection),
    m_pSessionObserver(pSessionObserver),
    m_pConnectionIO(nullptr),
    m_llUid(0)
    {
        m_pConnection->m_pConnectionObserver = this;
    }
    
    long long Session::getUid() {
        return m_llUid;
    }
    
    void Session::setConnectionIO(ConnectionIO *pConnectionIO) {
        m_pConnectionIO = pConnectionIO;
    }
    
    bool Session::send(const DataFormat *package) {
        if (!m_pConnectionIO) {
            printf("must set connectionIO when handle Session\r\n");
            return false;
        }
        return m_pConnectionIO->send(package, m_pConnection);
    }
    
    bool Session::read(ReseivePackageHandler reseiveHandler) {
        return m_pConnectionIO->read(reseiveHandler, m_pConnection);
    }
    
    void Session::onReadable(const Connection *pConnection) {
        m_pSessionObserver->onReadable(this);
    }
    
    void Session::onSendFaild(const Connection *pConnection) {
    }
    
    void Session::onReadFaild(const Connection *pConnection) {
    }
    
    void Session::onTimeOut(const Connection *pConnection) {
        m_pSessionObserver->onTimeOut(this);
    }
    
    
    

}
