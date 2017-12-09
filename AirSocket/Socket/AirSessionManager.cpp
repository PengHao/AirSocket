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
        if (pSession == nullptr) {
            return false;
        }
        return pSession->m_pBindConnection->send(package);
    }
    
    inline bool SessionManager::read(Session *pSession, ReseivePackageHandler reseiveHandler) {
        if (pSession == nullptr) {
            return false;
        }
        return pSession->m_pBindConnection->read(reseiveHandler);
    }
    
    inline void SessionManager::onReadable(const Connection *pConnection) {
        Session *pSession = getSession(pConnection);
        if (pSession == nullptr
            ||pSession->getBindConnection() == nullptr) {
            return;
        }
        pSession->lock();
        m_pSessionObserver->onReadable(pSession);
        pSession->unlock();
    }
    
    void SessionManager::onTimeOut(const Connection *pConnection) {
        if (pConnection == nullptr) {
            return;
        }
        m_pSessionObserver->onTimeOut(getSession(pConnection));
    }
    
    void SessionManager::onSendFaild(const Connection *pConnection) {
        if (pConnection == nullptr) {
            return;
        }
        m_pSessionObserver->onSendFaild(getSession(pConnection));
    }
    
    void SessionManager::onReadFaild(const Connection *pConnection) {
        if (pConnection == nullptr) {
            return;
        }
        m_pSessionObserver->onReadFaild(getSession(pConnection));
    }
    
    inline bool SessionManager::needObserving(const Connection *pConnection) {
        if (pConnection == nullptr) {
            return false;
        }
        return m_pSessionObserver->needObserving(getSession(pConnection));
    }
    
    void SessionManager::willBeDestroy(const Connection *pConnection) {
        Session *pSession = getSession(pConnection);
        if (pSession == nullptr) {
            return;
        }
        if ( pSession->m_pBindConnection == nullptr) {
            m_mapSessionMap.erase(pConnection->getHandle());
            m_pSessionObserver->willBeDestroy(pSession);
            delete pSession;
        }
    }
    
    SessionManager::~SessionManager() {
        for (std::pair<int, Session *> kv : m_mapSessionMap) {
            delete kv.second;
        }
    }
    
    void SessionManager::destroySession(Session *pSession) {
        if (pSession == nullptr) {
            return;
        }
        pSession->lock();
        pSession->m_pBindConnection = nullptr;
        pSession->unlock();
    }
    
    void SessionManager::addSession(Session *pSession) {
        if (pSession == nullptr) {
            return;
        }
        m_mapSessionMap[pSession->getBindConnection()->getHandle()] = pSession;
        m_pSessionObserver->onHandleNewSession(pSession);
    }
    
    
}
