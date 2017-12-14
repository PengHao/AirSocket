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
    
    
    ConnectionManager *ConnectionManager::create(ConnectionObserver *pConnectionObserver, ConnectionIOFactory *pConnectionIOFactory) {
        return new ConnectionManager(pConnectionObserver, pConnectionIOFactory);
    }
    
    Connection * ConnectionManager::create(const std::string &host, int port, int domainType, int dataType, int protocol) {
        FormatDataIO *pConnectionIO = m_pConnectionIOFactory->create();
        Connection *connection = new Connection(domainType, dataType, protocol, m_pConnectionObserver, pConnectionIO);
        if ( connection->init(host, port) == 0 ) {
            addObserver(connection);
            return connection;
        } else {
            delete connection;
            connection = nullptr;
        }
        return connection;
    }
    
    void ConnectionManager::destroyConnection(const Connection* connection) {
        if (connection == nullptr) {
            return;
        }
        
        Connection *pConnection = m_mapConnections[connection->getHandle()];
        m_mapConnections.erase(connection->getHandle());
        m_pConnectionObserver->willBeDestroy(pConnection);
    }
    
    Connection * ConnectionManager::create(Socket *ps) {
        if (ps == nullptr) {
            return nullptr;
        }
        FormatDataIO *pConnectionIO = m_pConnectionIOFactory->create();
        Connection *connection = new Connection(ps, m_pConnectionObserver, pConnectionIO);
        addObserver(connection);
        return connection;
    }
    
    ConnectionManager::~ConnectionManager() {
        delete m_pThread;
        for(const auto& kvp : m_mapConnections) {
            delete kvp.second;
        }
    }
    
    ConnectionManager::ConnectionManager(ConnectionObserver *pConnectionObserver, ConnectionIOFactory *pConnectionIOFactory) :
    m_pConnectionObserver(pConnectionObserver),
    m_pConnectionIOFactory(pConnectionIOFactory)
    {
        FD_ZERO(&m_ConnSet);
        m_pThread = new Thread();
        m_pThread->init();
        Thread::excute_async(m_pThread, [&] {
            select();
        });
        mTimeout.tv_sec = 0;
        mTimeout.tv_usec = 500000;
        mDefaultTimeOut.tv_sec = 0;
        mDefaultTimeOut.tv_usec = 500000;
    }
    
    bool ConnectionManager::addObserver(Connection *pConnection) {
        m_mapConnections[pConnection->getHandle()] = pConnection;
        return true;
    }
    
    void ConnectionManager::resetTimeOut() {
        m_ListWillTimeoutConnections.clear();
        for(const auto& kvp : m_mapConnections) {
            m_ListWillTimeoutConnections.push_back(kvp.first);
        }
        mTimeout = mDefaultTimeOut;
    }
    
    void ConnectionManager::selectTimeOut() {
        for (const auto &e : m_ListWillTimeoutConnections) {
            if (m_mapConnections[e]) {
                m_pConnectionObserver->onTimeOut(m_mapConnections[e]);
            }
        }
    }
    
    void ConnectionManager::selectError() {
        
    }
    
    void ConnectionManager::selectRead() {
        for(const auto& kvp : m_mapConnections) {
            if(FD_ISSET(kvp.first, &m_ConnSet)) {
                m_pConnectionObserver->onReadable(kvp.second);
                m_ListWillTimeoutConnections.remove(kvp.first);
            }
        }
        if (m_ListWillTimeoutConnections.size() == 0) {
            resetTimeOut();
        }
    }
    
    void ConnectionManager::select() {
        resetTimeOut();
        std::list<int> needRemoveConnectionHandles;
        int max = 0;
        while (true) {
            LOG_INFO("thread : %lld, select : %lld\r\n", m_pThread, this);
            max = 0;
            needRemoveConnectionHandles.clear();
            FD_ZERO(&m_ConnSet);
            for(const auto& kvp : m_mapConnections) {
                if (kvp.second != nullptr
                    && m_pConnectionObserver->needObserving(kvp.second)) {
                    FD_SET(kvp.first, &m_ConnSet);
#ifdef WIN32
					max = max(kvp.first, max);
#else
					max = std::max(kvp.first, max);
#endif
                }
                if (kvp.second == nullptr) {
                    needRemoveConnectionHandles.push_back(kvp.first);
                }
            }
            
            for (int handle : needRemoveConnectionHandles) {
                delete m_mapConnections[handle];
                m_mapConnections.erase(handle);
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
}



