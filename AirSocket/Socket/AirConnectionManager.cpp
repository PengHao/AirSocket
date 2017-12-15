//
//  AirConnectionObserverCenter.cpp
//  Socket
//
//  Created by 彭浩 on 16/7/9.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#include "AirConnectionManager.h"
#include "AirFormatDataIO.h"
#include "AirSocketDefine.h"
namespace AirCpp {
    
    ConnectionManager *ConnectionManager::create(ConnectionManagerDelegate *pConnectionObserver, ConnectionIOFactory *pConnectionIOFactory) {
        return new ConnectionManager(pConnectionObserver, pConnectionIOFactory);
    }
    
    Connection * ConnectionManager::create(const std::string &host, int port, int domainType, int dataType, int protocol) {
        FormatDataIO *pConnectionIO = m_pConnectionIOFactory->create();
        Connection *connection = new Connection(domainType, dataType, protocol, m_pConnectionObserver, pConnectionIO);
        if ( connection->init(host, port) == 0 ) {
            connection->setStatus(CONNECTED);
            m_mapConnections[connection->getHandle()] = connection;
            return connection;
        } else {
            delete connection;
            connection = nullptr;
        }
        return connection;
    }
    
    Connection * ConnectionManager::create(Socket *ps) {
        if (ps == nullptr) {
            return nullptr;
        }
        FormatDataIO *pConnectionIO = m_pConnectionIOFactory->create();
        Connection *connection = new Connection(ps, m_pConnectionObserver, pConnectionIO);
        m_mapConnections[connection->getHandle()] = connection;
        return connection;
    }
    
    ConnectionManager::~ConnectionManager() {
        if (m_pConnectionObserver) {
            m_pConnectionObserver->willBeTerminated(this);
        }
        delete m_pThread;
        for(const auto& kvp : m_mapConnections) {
            delete kvp.second;
        }
    }
    
    ConnectionManager::ConnectionManager(ConnectionManagerDelegate *pConnectionObserver, ConnectionIOFactory *pConnectionIOFactory) :
    m_pConnectionObserver(pConnectionObserver),
    m_pConnectionIOFactory(pConnectionIOFactory)
    {
        FD_ZERO(&m_ConnSet);
        m_pThread = new Thread();
        m_pThread->init();
        m_bActivate = true;
        mTimeout.tv_sec = 0;
        mTimeout.tv_usec = 500000;
        mDefaultTimeOut.tv_sec = 0;
        mDefaultTimeOut.tv_usec = 500000;
        Thread::excute_async(m_pThread, [&] {
            select();
            delete this;
        });
    }
    
    void ConnectionManager::terminate(bool needCallback) {
        if (!needCallback) {
            m_pConnectionObserver = nullptr;
        }
        m_bActivate = false;
    }
    
    void ConnectionManager::destroyConnection(const Connection* connection) {
        if (connection == nullptr) {
            return;
        }
        Connection *pConnection = m_mapConnections[connection->getHandle()];
        pConnection->setStatus(DISCONNECTED);
    }
    
    void ConnectionManager::resetTimeOut() {
        m_ListWillTimeoutConnections.clear();
        for(const auto& kvp : m_mapConnections) {
            m_ListWillTimeoutConnections.push_back(kvp.first);
        }
        mTimeout = mDefaultTimeOut;
    }
    
    void ConnectionManager::selectTimeOut() {
        if (!m_pConnectionObserver) {
            return;
        }
        for (const auto &e : m_ListWillTimeoutConnections) {
            if (m_mapConnections[e]) {
                m_pConnectionObserver->onTimeOut(m_mapConnections[e]);
            }
        }
    }
    
    void ConnectionManager::selectError() {
        
    }
    
    void ConnectionManager::select() {
        resetTimeOut();
        std::list<int> needRemoveConnectionHandles;
        int max = 0;
        while (m_bActivate) {
            LOG_INFO("thread : %lld, select : %lld\r\n", m_pThread, this);
            max = 0;
            needRemoveConnectionHandles.clear();
            FD_ZERO(&m_ConnSet);
            for(const auto& kvp : m_mapConnections) {
                if (kvp.second != nullptr
                    && kvp.second->getStatus() == CONNECTED
                    && m_pConnectionObserver
                    && m_pConnectionObserver->needObserving(kvp.second)) {
                    FD_SET(kvp.first, &m_ConnSet);
#ifdef WIN32
					max = max(kvp.first, max);
#else
					max = std::max(kvp.first, max);
#endif
                } else if (kvp.second == nullptr || kvp.second->getStatus() == DISCONNECTED) {
                    needRemoveConnectionHandles.push_back(kvp.first);
                }
            }
            
            for (int handle : needRemoveConnectionHandles) {
                Connection *pConnection = m_mapConnections[handle];
                if (pConnection) {
                    if (m_pConnectionObserver) {
                        m_pConnectionObserver->willBeDestroy(pConnection);
                    }
                    delete pConnection;
                }
                m_mapConnections.erase(handle);
            }
            
            if (max == 0) {
                sleep(1);
                continue;
            }
            
            int h = ::select(max + 1, &m_ConnSet, NULL, NULL, &mTimeout);
            switch (h) {
                case -1:
                    //clear set
                    selectError();
                    break;
                case 0:
                    //select timeout
                    selectTimeOut();
                    break;
                default:
                    //read
                    selectRead();
                    break;
            }
        }
    }
    
    void ConnectionManager::selectRead() {
        if (!m_pConnectionObserver) {
            return;
        }
        for(const auto& kvp : m_mapConnections) {
            if(FD_ISSET(kvp.first, &m_ConnSet)) {
                if (kvp.second&&kvp.second->getStatus() == CONNECTED) {
                    m_pConnectionObserver->onReadable(kvp.second);
                }
                m_ListWillTimeoutConnections.remove(kvp.first);
            }
        }
        if (m_ListWillTimeoutConnections.size() == 0) {
            resetTimeOut();
        }
    }
}



