//
//  AirConnectionObserverCenter.cpp
//  Socket
//
//  Created by 彭浩 on 16/7/9.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#include "AirConnectionObserverCenter.h"
namespace AirCpp {
    
    ConnectionObserverCenter* ConnectionObserverCenter::_defaultClent = nullptr;
    
    ConnectionObserverCenter *ConnectionObserverCenter::defaultObserverCenter() {
        if (_defaultClent == nullptr) {
            _defaultClent = new ConnectionObserverCenter();
        }
        return _defaultClent;
    }
    
    
    ConnectionObserverCenter::ConnectionObserverCenter() {
        FD_ZERO(&m_ConnSet);
        m_pThread = new Thread();
        m_pThread->init();
        Thread::excute_async(m_pThread, [&] {
            select();
        });
        mTimeout.tv_sec = 10;
        mTimeout.tv_usec = 0;
        mDefaultTimeOut.tv_sec = 10;
        mDefaultTimeOut.tv_usec = 0;
    }
    
    bool ConnectionObserverCenter::addObserver(Connection *connection, ConnectionObserver *connectionObserver) {
        Element element;
        element.m_pConnection = connection;
        element.m_pConnectionObserver = connectionObserver;
        m_mapConnectionObservers[connection->m_pSocket->m_iSocketHandle] = element;
        return true;
    }
    
    void ConnectionObserverCenter::resetTimeOut() {
        m_ListWillTimeoutConnections.clear();
        for(const auto& kvp : m_mapConnectionObservers) {
            m_ListWillTimeoutConnections.push_back(kvp.first);
        }
        mTimeout = mDefaultTimeOut;
    }
    
    void ConnectionObserverCenter::onTimeOut() {
        for (const auto &e : m_ListWillTimeoutConnections) {
            m_mapConnectionObservers[e].m_pConnectionObserver->onTimeOut(m_mapConnectionObservers[e].m_pConnection);
        }
    }
    
    void ConnectionObserverCenter::onError() {
        
    }
    
    void ConnectionObserverCenter::onRead() {
        for(const auto& kvp : m_mapConnectionObservers) {
            if(FD_ISSET(kvp.first, &m_ConnSet)) {
                try {
                    kvp.second.m_pConnectionObserver->onReadable(kvp.second.m_pConnection);
                } catch (std::exception &e) {
                    
                }
                m_ListWillTimeoutConnections.remove(kvp.first);
            }
        }
        if (m_ListWillTimeoutConnections.size() == 0) {
            resetTimeOut();
        }
    }
    
    void ConnectionObserverCenter::select() {
        resetTimeOut();
        while (true) {
            FD_ZERO(&m_ConnSet);
            int max = 0;
            for(const auto& kvp : m_mapConnectionObservers) {
                if (kvp.second.m_pConnection != nullptr) {
                    FD_SET(kvp.first, &m_ConnSet);
                    max = std::max(kvp.first, max);
                }
            }
            
            int h = ::select(max + 1, &m_ConnSet, NULL, NULL, &mTimeout);
            switch (h) {
                case -1:
                    //clear set
                    onError();
                    continue;
                case 0:
                    //select timeout
                    onTimeOut();
                    continue;
                default:
                    //read
                    onRead();
                    continue;
            }
        }
    }
}



