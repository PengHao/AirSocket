//
//  AirSessionManager.cpp
//  AirSocket
//
//  Created by peng hao on 2017/11/22.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include "AirSessionManager.h"
namespace AirCpp {
    SessionManager::SessionManager(SessionObserver *pSessionObserver):
    m_pSessionObserver(pSessionObserver)
    {
        
    }
    
    inline Session *SessionManager::getSession(long long uid) {
        for (std::pair<int, Session *> kv : m_mapSessionMap) {
            if (kv.second && kv.second->getUid() == uid) {
                return kv.second;
            }
        }
        return nullptr;
    }
    
    inline bool SessionManager::send(Session *pSession, const FormatedData *package) {
        return pSession->m_pConnection->send(package);
    }
    
    inline bool SessionManager::read(Session *pSession, ReseivePackageHandler reseiveHandler) {
        return pSession->m_pConnection->read(reseiveHandler);
    }
    
    inline void SessionManager::onReadable(const Connection *pConnection) {
        m_pSessionObserver->onReadable(getSession(pConnection));
    }
    
    void SessionManager::onTimeOut(const Connection *pConnection) {
        m_pSessionObserver->onTimeOut(getSession(pConnection));
    }
    
    void SessionManager::onSendFaild(const Connection *pConnection) {
        m_pSessionObserver->onSendFaild(getSession(pConnection));
    }
    
    void SessionManager::onReadFaild(const Connection *pConnection) {
        m_pSessionObserver->onReadFaild(getSession(pConnection));
    }
    
    inline bool SessionManager::needObserving(const Connection *pConnection) {
        return m_pSessionObserver->needObserving(getSession(pConnection));
    }
    
    void SessionManager::willBeDestroy(const Connection *pConnection) {
        m_pSessionObserver->willBeDestroy(getSession(pConnection));
    }
    
    SessionManager::~SessionManager() {
        for (std::pair<int, Session *> kv : m_mapSessionMap) {
            delete kv.second;
        }
    }
    
    void SessionManager::destroySession(Session *pSession) {
        m_mapSessionMap.erase(pSession->m_pConnection->getHandle());
        delete pSession;
    }
    
    void SessionManager::addSession(Session *pSession) {
        m_mapSessionMap[pSession->getConnection()->getHandle()] = pSession;
        m_pSessionObserver->onHandleNewSession(pSession);
    }
    
    
}
