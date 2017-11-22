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
    ConnectionPackageIO::ConnectionPackageIO() :
    pCurrentPackage(nullptr){
    }
    
    void ConnectionPackageIO::fillData(unsigned long long len, char *data, FillPackageCallBack handleFilledPackage) {
        if (!pCurrentPackage) {
            pCurrentPackage = new Package();
        }
        
        unsigned long long sizeofSize = sizeof(pCurrentPackage->m_ullSize);
        unsigned char *pOffset = (unsigned char *)&pCurrentPackage->m_ullSize;
        char *pDataOffset = data;
        if (pCurrentPackage->m_ullFilledSize < sizeofSize) {
            pOffset += pCurrentPackage->m_ullFilledSize;
            auto s = std::min(sizeofSize - pCurrentPackage->m_ullFilledSize, len);
            memcpy(pOffset, pDataOffset, s);
            pCurrentPackage->m_ullFilledSize += s;
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
            size_t settedDataSize = pCurrentPackage->m_ullFilledSize - sizeofSize;
            size_t unsetDataSize = pCurrentPackage->m_ullSize - settedDataSize;
            pOffset += settedDataSize;
            if (unsetDataSize <= len) {
                memcpy(pOffset, data, unsetDataSize);
                pCurrentPackage->m_ullFilledSize += unsetDataSize;
                handleFilledPackage(pCurrentPackage);
                len -= unsetDataSize;
                pDataOffset += unsetDataSize;
                delete pCurrentPackage;
                pCurrentPackage = nullptr;
                if (len > 0) {
                    fillData(len, pDataOffset, handleFilledPackage);
                }
            } else {
                memcpy(pOffset, data, len);
                pCurrentPackage->m_ullFilledSize += len;
            }
        }
    }
    
    ConnectionPackageIO::~ConnectionPackageIO() {
    }
    
    bool ConnectionPackageIO::send(const DataFormat *package, Connection *pConnection) {
        std::string dataString;
        if (package->serial(dataString)) {
            long long len = pConnection->send(dataString.c_str(), dataString.length());
            if (len == -1) {
                //socket error
                return false;
            }
            return true;
        }
        return false;
    }
    
    bool ConnectionPackageIO::read(ReseivePackageHandler reseiveHandler, Connection *pConnection) {
        memset(m_strTempBuffer, 0, TEMP_BUFFER_SIZE);
        long long size = pConnection->read(m_strTempBuffer, TEMP_BUFFER_SIZE);
        if (size <= 0) {
            return false;
        }
        
        fillData(size, m_strTempBuffer, [=](const Package *package){
            reseiveHandler(package);
        });
        return true;
    }
}
