//
//  AirConnectionPackageIO.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include "AirConnectionPackageIO.h"
namespace AirCpp {
    ConnectionPackageIO::ConnectionPackageIO(Connection *pConnection) :
    m_pConnection(pConnection),
    pCurrentPackage(nullptr){
    }
    
    void ConnectionPackageIO::fillData(unsigned long long len, char *data, FillPackageCallBack handleFilledPackage) {
        if (!pCurrentPackage) {
            pCurrentPackage = new Package();
        }
        
        unsigned long long sizeofSize = sizeof(pCurrentPackage->m_ullSize);
        unsigned char *pOffset = (unsigned char *)&pCurrentPackage->m_ullSize;
        char *pDataOffset = data;
        if (pCurrentPackage->m_ullSettedSize < sizeofSize) {
            pOffset += pCurrentPackage->m_ullSettedSize;
            auto s = std::min(sizeofSize - pCurrentPackage->m_ullSettedSize, len);
            memcpy(pOffset, pDataOffset, s);
            pCurrentPackage->m_ullSettedSize += s;
            pDataOffset += s;
            len -= s;
            if (len > 0) {
                fillData(len, pDataOffset, handleFilledPackage);
            }
        } else {
            if (pCurrentPackage->m_ullSize <= 0) {
                return;
            }
            if (pCurrentPackage->m_pData == nullptr) {
                pCurrentPackage->m_pData = (unsigned char *)calloc(pCurrentPackage->m_ullSize, sizeof(unsigned char));
            }
            pOffset = pCurrentPackage->m_pData;
            size_t settedDataSize = pCurrentPackage->m_ullSettedSize - sizeofSize;
            size_t unsetDataSize = pCurrentPackage->m_ullSize - settedDataSize;
            pOffset += settedDataSize;
            if (unsetDataSize <= len) {
                memcpy(pOffset, data, unsetDataSize);
                pCurrentPackage->m_ullSettedSize += unsetDataSize;
                handleFilledPackage(pCurrentPackage);
                printf("FillData : %llu \r\n", pCurrentPackage->m_ullSize);
                len -= unsetDataSize;
                pDataOffset += unsetDataSize;
                delete pCurrentPackage;
                pCurrentPackage = nullptr;
                if (len > 0) {
                    fillData(len, pDataOffset, handleFilledPackage);
                }
            } else {
                memcpy(pOffset, data, len);
                pCurrentPackage->m_ullSettedSize += len;
            }
        }
    }

    ConnectionPackageIO *ConnectionPackageIO::Create(Connection *pConnection) {
        ConnectionPackageIO *packageConnection = new ConnectionPackageIO(pConnection);
        return packageConnection;
    }
    
    ConnectionPackageIO::~ConnectionPackageIO() {
    }
    
    bool ConnectionPackageIO::send(const Package *package) {
        long long len = m_pConnection->send((const char *)&package->m_ullSettedSize, sizeof(&package->m_ullSettedSize));
        if (len == -1) {
            //socket error
            return false;
        } if (len != sizeof(&package->m_ullSettedSize)) {
            return false;
        }
        len = m_pConnection->send((const char *)package->m_pData, package->m_ullSettedSize);
        return len == package->m_ullSettedSize;
    }
    
    void ConnectionPackageIO::read(ReseivePackageHandler reseiveHandler) {
        memset(m_strTempBuffer, 0, TEMP_BUFFER_SIZE);
        long long size = m_pConnection->read(m_strTempBuffer, TEMP_BUFFER_SIZE);
        if (size <= 0) {
            return;
        }
        
        fillData(size, m_strTempBuffer, [=](const Package *package){
            reseiveHandler(package, m_pConnection);
        });
    }
}
