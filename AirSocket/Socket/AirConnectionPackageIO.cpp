//
//  AirConnectionPackageIO.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include "AirConnectionPackageIO.h"
#include "AirFormatDataIO.h"
namespace AirCpp {
    ConnectionPackageIO::ConnectionPackageIO() :
    pCurrentPackage(nullptr){
    }
    
    void ConnectionPackageIO::fillData(unsigned long long len, char *data, ReseivePackageHandler reseiveHandler) {
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
                fillData(len, pDataOffset, reseiveHandler);
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
                pCurrentPackage->m_ullFilledSize += len;
            }
        }
    }
    
    ConnectionPackageIO::~ConnectionPackageIO() {
    }
    
}
