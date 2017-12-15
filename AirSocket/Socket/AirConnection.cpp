//
//  AirConnection.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include <errno.h>
#include "AirConnection.h"
#include "AirFormatDataIO.h"
#include "AirConnectionManagerDelegate.h"
#include "AirSocketDefine.h"

namespace AirCpp {
    
    Connection::~Connection() {
        LOG_INFO("connection deleted\r\n");
        delete m_pSocket;
        delete m_pConnectionIO;
    }
    
    Connection::Connection(int domainType, int dataType, int protocol, ConnectionManagerDelegate * pConnectionObserver, FormatDataIO *pConnectionIO):
    m_iDomainType(domainType),
    m_iDataType(dataType),
    m_iProtocol(protocol),
    m_pConnectionIO(pConnectionIO),
    m_pSocket(nullptr)
    {
        
    }
    
    Connection::Connection(Socket *ps, ConnectionManagerDelegate * pConnectionObserver, FormatDataIO *pConnectionIO):
    m_pSocket(ps),
    m_pConnectionIO(pConnectionIO),
    m_status(CONNECTED)
    {
    }
    
    int Connection::init(const std::string &host, int port) {
        m_iPort = port;
        m_strHost = host;
        return reconnect();
    }
    
    Status Connection::getStatus() {
        return m_status;
    }
    
    void Connection::setStatus(Status status) {
        m_status = status;
    }
    
    int Connection::reconnect() {
        if (m_pSocket) {
            delete m_pSocket;
        }
        
        m_pSocket = new Socket();
        int rs = m_pSocket->init(m_iDomainType, m_iDataType, m_iProtocol);
        if (rs == 0) {
            rs = m_pSocket->connect(m_strHost, m_iPort);
        }
        if (rs == 0) {
            setStatus(CONNECTED);
        }
        return rs;
    }
    
    int Connection::getHandle() const {
        return m_pSocket->m_iSocketHandle;
    }
    
    bool Connection::send(const FormatedData *package) const {
        std::string dataString;
        if (package->serial(dataString)) {
            long long len = m_pSocket->send(dataString.c_str(), dataString.length());
            if (len > 0 || errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN) {
                return true;
            }
        }
        return false;
    }
    
    bool Connection::read(ReseivePackageHandler reseiveHandler) const {
        char m_strTempBuffer[TEMP_BUFFER_SIZE] = {0};
        ssize_t size = m_pSocket->read(m_strTempBuffer, TEMP_BUFFER_SIZE);
        if (size < 0) {
            return errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN;
        } else if (size == 0) {
            printf("connection closed by remoute");
            return false;
        }
        m_pConnectionIO->fillData(size, m_strTempBuffer, reseiveHandler);
        return true;
    }
}
