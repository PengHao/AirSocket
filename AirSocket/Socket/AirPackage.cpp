//
//  AirPackage.cpp
//  Socket
//
//  Created by 彭浩 on 16/7/26.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#include "AirPackage.h"
#include "AirSocketDefine.h"
namespace AirCpp {
    
    Package::Package():
    m_ullSize(0),
    m_ullFilledSize(0),
    m_pData(nullptr) {
        
    }
    
    
    bool Package::getContent(std::string &contentData) const {
        contentData.clear();
        contentData.append((char *)m_pData, m_ullSize);
        return true;
    }
    
    bool Package::setContent(const std::string &contentData) {
        if (m_pData) {
            free(m_pData);
            m_pData = nullptr;
        }
        m_pData = (unsigned char *)calloc(sizeof(char), contentData.size());
        memcpy(m_pData, contentData.c_str(), contentData.size());
        return true;
    }
    
    bool Package::serial(std::string &serilazeString) const{
        serilazeString.clear();
        serilazeString.append((char *)&m_ullSize, sizeof(m_ullSize));
        serilazeString.append((char *)m_pData, m_ullSize);
        return true;
    }
    
    bool Package::deserial(std::string &deserialString) {
        size_t leftSize = deserialString.size();
        if (leftSize < sizeof(m_ullSize)) {
            return false;
        }
        const char* pData = deserialString.c_str();
        memcpy(&m_ullSize, pData, sizeof(m_ullSize));
        leftSize -= sizeof(m_ullSize);
        if (m_ullSize > leftSize) {
            LOG_INFO("data broken");
            return false;
        } else {
            m_pData = (unsigned char *)calloc(sizeof(char), m_ullSize);
            memcpy(m_pData, pData+sizeof(m_ullSize), m_ullSize);
        }
        
        return true;
    }
    
    Package::Package(const std::string &data) {
        m_ullSize = data.size();
        m_pData = (unsigned char *)calloc(sizeof(char), m_ullSize);
        memcpy(m_pData, data.c_str(), m_ullSize);
        m_ullFilledSize = m_ullSize+sizeof(m_ullSize);
    }
    
    Package::~Package() {
        LOG_INFO("delete Package\r\n");
        if (m_pData) {
            free(m_pData);
        }
        m_pData = nullptr;
        m_ullSize = 0;
    }

}

