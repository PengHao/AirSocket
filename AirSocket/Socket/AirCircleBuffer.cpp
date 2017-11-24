//
//  AirCircleBuffer.cpp
//  AirSocket
//
//  Created by peng hao on 2017/11/24.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include "AirCircleBuffer.h"
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
}
