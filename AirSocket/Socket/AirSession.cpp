//
//  AirSession.cpp
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/18.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include "AirSession.h"
#include "AirSocketDefine.h"
namespace AirCpp {

    void Session::setUid(long long uid) {
        m_llUid = uid;
    }
    
    Session::Session(const Connection *pConnection):
    m_pBindConnection(pConnection),
    m_llUid(0)
    {
        m_pLock = new Lock();
        m_pLock->init(LOCK_TYPE_RECURSIVE);
    }
    
    const Connection *Session::getBindConnection() {
        return m_pBindConnection;
    }
    
    long long Session::getUid() {
        return m_llUid;
    }
    
    Session::~Session(){
        LOG_INFO("delete session");
        delete m_pLock;
    }

}
