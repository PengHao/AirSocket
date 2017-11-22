//
//  AirSessionManager.cpp
//  AirSocket
//
//  Created by peng hao on 2017/11/22.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include "AirSessionManager.h"
namespace AirCpp {
    
    SessionManager::SessionManager() {
        m_pConnectionOberverCenter = ConnectionObserverCenter::defaultObserverCenter();
    }
    
    SessionManager::~SessionManager() {
        for (std::pair<int, Session *> kv : m_mapSessionMap) {
            delete kv.second;
        }
        m_pConnectionOberverCenter = nullptr;
    }
    
    Session *SessionManager::create(Connection *pConnection) {
        Session *pSession = new Session(pConnection, this);
        m_pConnectionOberverCenter->addObserver(pConnection);
        m_mapSessionMap[pConnection->getHandle()] = pSession;
        onHandleNewSession(pSession);
        return pSession;
    }
    
    
}
