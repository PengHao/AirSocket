//
//  AirPackage.cpp
//  Socket
//
//  Created by 彭浩 on 16/7/26.
//  Copyright © 2016年 彭浩. All rights reserved.
//
#include <string.h>
#include <stdlib.h>
#include "AirPackage.h"
#include "AirSocketDefine.h"
namespace AirCpp {
    
    Package::Package():
    m_ulSize(0),
    m_ulFilledSize(0),
    m_pData(nullptr) {
        
    }
    
    
    bool Package::getContent(std::string &contentData) const {
        contentData.clear();
        contentData.append((char *)m_pData, m_ulSize);
        return true;
    }
    
    bool Package::setContent(const std::string &contentData) {
        if (m_pData) {
            free(m_pData);
            m_pData = nullptr;
        }
        m_pData = (unsigned char *)calloc(sizeof(unsigned char), contentData.size());
        memcpy(m_pData, contentData.c_str(), contentData.size());
        return true;
    }
    
    bool Package::serial(std::string &serilazeString) const{
        serilazeString.clear();
        serilazeString.append((char *)&m_ulSize, sizeof(m_ulSize));
        serilazeString.append((char *)m_pData, m_ulSize);
        return true;
    }
    
    bool Package::deserial(std::string &deserialString) {
        size_t leftSize = deserialString.size();
        if (leftSize < sizeof(m_ulSize)) {
            return false;
        }
        const char* pData = deserialString.c_str();
        memcpy(&m_ulSize, pData, sizeof(m_ulSize));
        leftSize -= sizeof(m_ulSize);
        if (m_ulSize > leftSize) {
            LOG_INFO("data broken");
            return false;
        } else {
            m_pData = (unsigned char *)calloc(sizeof(unsigned char), m_ulSize);
            memcpy(m_pData, pData+sizeof(m_ulSize), m_ulSize);
        }
        
        return true;
    }
    
    Package::Package(const std::string &data) {
        m_ulSize = data.size();
        m_pData = (unsigned char *)calloc(sizeof(unsigned char), m_ulSize);
        memcpy(m_pData, data.c_str(), m_ulSize);
        m_ulFilledSize = m_ulSize+sizeof(m_ulSize);
    }
    
    Package::~Package() {
        LOG_INFO("delete Package\r\n");
        if (m_pData) {
            free(m_pData);
        }
        m_pData = nullptr;
        m_ulSize = 0;
    }

}

