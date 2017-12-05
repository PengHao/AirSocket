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
    CircleBuffer::CircleBuffer(size_t size) :
    m_llSize(size),
    m_llAvaliableSize(size)
    {
        m_pBuffer = (char *)calloc(size, sizeof(char));
        m_pWrite = m_pBuffer;
        m_pRead = m_pBuffer;
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m_mutex, &attr);
    }
    
    CircleBuffer::~CircleBuffer() {
        free(m_pBuffer);
        pthread_mutex_destroy(&m_mutex);
    }
    
    size_t CircleBuffer::_write(const char *pRes, size_t length) {
        
        if (m_llAvaliableSize == 0) {
            return 0;
        }
        
        if (m_llAvaliableSize < length) {
            return write(pRes, m_llAvaliableSize);
        }
        size_t writedSize = 0;
        size_t rightEmpty = m_llSize - (m_pWrite - m_pBuffer);
        if (length > rightEmpty) {
            writedSize += write(pRes, rightEmpty);
            length -= writedSize;
            pRes += writedSize;
        }
        memcpy(m_pWrite, pRes, length);
        m_llAvaliableSize -= length;
        m_pWrite += length;
        writedSize += length;
        if (m_pWrite - m_pBuffer == m_llSize) {
            m_pWrite = m_pBuffer;
        }
        return writedSize;
    }
    
    size_t CircleBuffer::_read(char *res, size_t length) {
        size_t readAbleSize = m_llSize - m_llAvaliableSize;
        if (readAbleSize == 0) {
            return 0;
        }
        if (readAbleSize < length) {
            return read(res, readAbleSize);
        }
        size_t readedSize = 0;
        size_t readRightSize = m_llSize - (m_pRead - m_pBuffer);
        if (length > readRightSize) {
            readedSize += read(res, readRightSize);
            length -= readRightSize;
            res += readRightSize;
        }
        memcpy(res, m_pRead, length);
        m_llAvaliableSize += length;
        m_pRead += length;
        readedSize += length;
        if (m_pRead - m_pBuffer == m_llSize) {
            m_pRead = m_pBuffer;
        }
        return readedSize;
    }
    
    size_t CircleBuffer::getWriteAvailableBytesSize() {
        return m_llAvaliableSize;
    }
    
    CircleBuffer *CircleBuffer::Create(size_t length) {
        return new CircleBuffer(length);
    }
    
    void CircleBuffer::clean() {
        pthread_mutex_lock(&m_mutex);
        memset(m_pBuffer, 0, m_llSize);
        m_pRead = m_pBuffer;
        m_pWrite = m_pBuffer;
        m_llAvaliableSize = m_llSize;
        pthread_mutex_unlock(&m_mutex);
    }
    
    size_t CircleBuffer::write(const char *pRes, size_t length) {
        pthread_mutex_lock(&m_mutex);
        size_t writedSize = _write(pRes, length);
        pthread_mutex_unlock(&m_mutex);
        return writedSize;
    }
    
    size_t CircleBuffer::read(char *res, size_t length) {
        pthread_mutex_lock(&m_mutex);
        size_t readedSize = _read(res, length);
        pthread_mutex_unlock(&m_mutex);
        return readedSize;
    }
}
