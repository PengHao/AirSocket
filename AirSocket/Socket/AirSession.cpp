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
    m_llUid(0)
    {
        
    }
    
    long long Session::getUid() {
        return m_llUid;
    }
    
    Connection* Session::getConnection() {
        return m_pConnection;
    }
    
    void Session::setConnectionIO(ConnectionIO *pConnectionIO) {
        m_pConnectionIO = pConnectionIO;
    }
    
    bool Session::send(const Package *package) {
        return m_pConnectionIO->send(package);
    }
    
    void Session::read(ReseivePackageHandler reseiveHandler) {
        m_pConnectionIO->read(reseiveHandler);
    }
    
    SessionManager* SessionManager::_defaultSessionManager = nullptr;
    
    SessionManager::SessionManager() {
        m_pConnectionOberverCenter = ConnectionObserverCenter::defaultObserverCenter();
    }
    
    SessionManager::~SessionManager() {
        for (std::pair<int, Session *> kv : m_mapSessionMap) {
            delete kv.second;
        }
        m_pConnectionOberverCenter = nullptr;
    }
    
    SessionManager *SessionManager::defaultSessionManager() {
        if (!_defaultSessionManager) {
            _defaultSessionManager = new SessionManager();
        }
        return _defaultSessionManager;
    }
    
    void SessionManager::onReadable(const Connection *pConnection) {
        Session *pSession = getSession(pConnection);
        if (pSession) {
            pSession->m_pSessionObserver->onReadable(pSession);
        }
    }
    
    void SessionManager::onTimeOut(const Connection *pConnection) {
        Session *pSession = getSession(pConnection);
        if (!pSession) {
            printf("no session found for connection");
            return;
        }
        
        bool needDisconnect = false;
        pSession->m_pSessionObserver->onTimeOut(pSession, &needDisconnect);
        if (!needDisconnect) {
            return;
        }
        m_mapSessionMap.erase(pConnection->getHandle());
        delete pSession;
    }
    
    Session *SessionManager::getSession(const Connection *pConnection) {
        return m_mapSessionMap[pConnection->getHandle()];
    }
    
    Session *SessionManager::create(Connection *pConnection, SessionObserver *pSessionObserver) {
        Session *pSession = new Session(pConnection, pSessionObserver);
        m_pConnectionOberverCenter->addObserver(pConnection, this);
        m_mapSessionMap[pConnection->getHandle()] = pSession;
        return pSession;
    }
    

}
