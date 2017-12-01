//
//  AirConnection.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include "AirConnection.h"
#include "AirFormatDataIO.h"
#include "AirConnectionObserver.h"
#include "AirSocketDefine.h"

namespace AirCpp {
    
    Connection::~Connection() {
        LOG_INFO("connection deleted\r\n");
        delete m_pSocket;
        delete m_pConnectionIO;
    }
    
    Connection::Connection(int domainType, int dataType, int protocol, ConnectionObserver * pConnectionObserver, FormatDataIO *pConnectionIO):
    m_iDomainType(domainType),
    m_iDataType(dataType),
    m_iProtocol(protocol),
    m_pConnectionObserver(pConnectionObserver),
    m_pConnectionIO(pConnectionIO),
    m_pSocket(nullptr)
    {
        
    }
    
    Connection::Connection(Socket *ps, ConnectionObserver * pConnectionObserver, FormatDataIO *pConnectionIO):
    m_pSocket(ps),
    m_pConnectionIO(pConnectionIO),
    m_pConnectionObserver(pConnectionObserver)
    {
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
    
    void Connection::onTimeOut() {
        if (m_pConnectionObserver) {
            m_pConnectionObserver->onTimeOut(this);
        }
    }
    
    void Connection::onReadable() {
        if (m_pConnectionObserver) {
            m_pConnectionObserver->onReadable(this);
        }
    }
    
    bool Connection::send(const FormatedData *package) const {
        std::string dataString;
        if (package->serial(dataString)) {
            long long len = send(dataString.c_str(), dataString.length());
            if (len == -1) {
                //socket error
                return false;
            }
            return true;
        }
        return false;
    }
    
    bool Connection::read(ReseivePackageHandler reseiveHandler) const {
        char m_strTempBuffer[TEMP_BUFFER_SIZE] = {0};
        long long size = m_pSocket->read(m_strTempBuffer, TEMP_BUFFER_SIZE);
        if (size <= 0) {
            return false;
        }
        m_pConnectionIO->fillData(size, m_strTempBuffer, reseiveHandler);
        return true;
    }
    
    
    long long Connection::send(const char *c_data, long long length) const {
        long long rs = m_pSocket->send(c_data, length);
        if (rs < 0) {
            if (m_pConnectionObserver) {
                m_pConnectionObserver->onSendFaild(this);
            }
        }
        return rs;
    }
}
