//
//  AirConnectionPackageIO.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "AirConnectionPackageIO.h"
#include "AirFormatDataIO.h"
#include "AirSocketDefine.h"
namespace AirCpp {
    ConnectionPackageIO::ConnectionPackageIO() :
    pCurrentPackage(nullptr){
    }
    
    void ConnectionPackageIO::fillData(ssize_t len, char *data, ReseivePackageHandler reseiveHandler) {
        if (!pCurrentPackage) {
            pCurrentPackage = new Package();
        }
        
        size_t sizeofSize = sizeof(pCurrentPackage->m_ulSize);
        unsigned char *pOffset = (unsigned char *)&pCurrentPackage->m_ulSize;
        char *pDataOffset = data;
        if (pCurrentPackage->m_ulFilledSize < sizeofSize) {
            pOffset += pCurrentPackage->m_ulFilledSize;

#ifdef WIN32
            size_t s = min(sizeofSize - pCurrentPackage->m_ullFilledSize, len);
#else
			size_t s = fmin(sizeofSize - pCurrentPackage->m_ulFilledSize, len);
#endif
            memcpy(pOffset, pDataOffset, s);
            pCurrentPackage->m_ulFilledSize += s;
            pDataOffset += s;
            len -= s;
            if (len > 0) {
                fillData(len, pDataOffset, reseiveHandler);
            }
        } else {
            if (pCurrentPackage->m_ulSize <= 0) {
                return;
            }
            if (pCurrentPackage->m_pData == nullptr) {
                pCurrentPackage->m_pData = (unsigned char *)calloc(pCurrentPackage->m_ulSize, sizeof(unsigned char));
            }
            pOffset = pCurrentPackage->m_pData;
            size_t settedDataSize = pCurrentPackage->m_ulFilledSize - sizeofSize;
            size_t unsetDataSize = pCurrentPackage->m_ulSize - settedDataSize;
            pOffset += settedDataSize;
            if (unsetDataSize <= len) {
                memcpy(pOffset, data, unsetDataSize);
                pCurrentPackage->m_ulFilledSize += unsetDataSize;
                reseiveHandler(pCurrentPackage);
                len -= unsetDataSize;
                pDataOffset += unsetDataSize;
                delete pCurrentPackage;
                pCurrentPackage = nullptr;
                if (len > 0) {
                    fillData(len, pDataOffset, reseiveHandler);
                }
            } else {
                memcpy(pOffset, data, len);
                pCurrentPackage->m_ulFilledSize += len;
            }
        }
    }
    
    ConnectionPackageIO::~ConnectionPackageIO() {
        LOG_INFO("delete connection package\r\n");
        delete pCurrentPackage;
    }
    
}
