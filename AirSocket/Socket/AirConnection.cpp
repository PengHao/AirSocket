//
//  AirConnection.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include "AirConnection.h"

namespace AirCpp {
    
    Connection::~Connection() {
        delete m_pSocket;
    }
    
    Connection::Connection(int domainType, int dataType, int protocol):
    m_iDomainType(domainType),
    m_iDataType(dataType),
    m_iProtocol(protocol),
    m_pSocket(nullptr)
    {
        
    }
    
    Connection::Connection(Socket *ps):
    m_pSocket(ps)
    {
    }
    
    Connection * Connection::Create(const std::string &host, int port, int domainType, int dataType, int protocol) {
        Connection *connection = new Connection(domainType, dataType, protocol);
        if ( connection->init(host, port) == 0 ) {
            return connection;
        } else {
            delete connection;
            connection = nullptr;
        }
        return connection;
    }
    
    
    int Connection::init(const std::string &host, int port) {
        m_pSocket = new Socket();
        int rs = m_pSocket->init(m_iDomainType, m_iDataType, m_iProtocol);
        if (rs == 0) {
            return m_pSocket->connect(host, port);
        } else {
            return rs;
        }
    }
    
    int Connection::getHandle() const {
        return m_pSocket->m_iSocketHandle;
    }
    
    long long Connection::read(char *c_data, long long length) const {
        return m_pSocket->read(c_data, length);
    }
    
    long long Connection::send(const char *c_data, long long length) const {
        return m_pSocket->send(c_data, length);
    }
}
