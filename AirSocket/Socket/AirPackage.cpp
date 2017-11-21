//
//  AirPackage.cpp
//  Socket
//
//  Created by 彭浩 on 16/7/26.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#include "AirPackage.h"
#include "TPCircularBuffer.h"

namespace AirCpp {
    class TPCircularBufferContainor{
    public:
        TPCircularBuffer *m_pTPCircularBuffer;
    };
    
    CircleBuffer::CircleBuffer(int32_t size) :
    m_iSize(size)
    {
        if (m_iSize ==0) {
            return;
        }
        m_pTPCircularBufferContainor = new TPCircularBufferContainor();
        m_pTPCircularBufferContainor->m_pTPCircularBuffer = (TPCircularBuffer *)calloc(1, sizeof(TPCircularBuffer));
        TPCircularBufferInit(m_pTPCircularBufferContainor->m_pTPCircularBuffer, m_iSize);
        TPCircularBufferClear(m_pTPCircularBufferContainor->m_pTPCircularBuffer);
        TPCircularBufferSetAtomic(m_pTPCircularBufferContainor->m_pTPCircularBuffer, true);
    };

    CircleBuffer* CircleBuffer::Create(int32_t size) {
        return new CircleBuffer(size);
        
    }
    
    int32_t CircleBuffer::read(char *c_data, int32_t length) {
        int32_t availableBytes = 0;
        void *bufferTail = TPCircularBufferTail(m_pTPCircularBufferContainor->m_pTPCircularBuffer, &availableBytes);
        int32_t readLen  =  length > availableBytes ? availableBytes : length;
        memcpy(c_data, bufferTail, readLen);
        TPCircularBufferConsume(m_pTPCircularBufferContainor->m_pTPCircularBuffer, readLen);
        return readLen;
    }
    
    int32_t CircleBuffer::getWriteAvailableBytesSize() {
        int32_t availableBytes = 0;
        TPCircularBufferHead(m_pTPCircularBufferContainor->m_pTPCircularBuffer, &availableBytes);
        return availableBytes;
    }
    
    int32_t CircleBuffer::write(const char *c_data, int32_t length) {
        int32_t availableBytes = getWriteAvailableBytesSize();
        if (availableBytes <= 0) {
            return 0;
        }
        
        int32_t writeLen  =  availableBytes >= length ? length : availableBytes;
        TPCircularBufferProduceBytes(m_pTPCircularBufferContainor->m_pTPCircularBuffer, c_data, writeLen);
        return writeLen;
    }
    
    
    
    Package::Package():
    m_ullSize(0),
    m_ullSettedSize(0),
    m_pData(nullptr) {
        
    }
    
    Package::Package(const std::string &data) {
        m_ullSize = data.size();
        m_ullSettedSize = data.size();
        m_pData = (unsigned char *)calloc(sizeof(char), m_ullSettedSize);
        memcpy(m_pData, data.c_str(), m_ullSettedSize);
    }
    
    Package::~Package() {
        free(m_pData);
        m_pData = nullptr;
        m_ullSize = 0;
    }

}

