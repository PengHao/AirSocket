//
//  AirCircleBuffer.hpp
//  AirSocket
//
//  Created by peng hao on 2017/11/24.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirCircleBuffer_hpp
#define AirCircleBuffer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
namespace AirCpp {
    class CircleBuffer {
    private:
        char *m_pBuffer;
        char *m_pEnd;
        size_t m_llSize;
        size_t m_llAvaliableSize;
        char *m_pRead;
        char *m_pWrite;
        pthread_mutex_t  m_mutex;
        
    protected:
        CircleBuffer(size_t size);
        
        size_t _write(const char *pRes, size_t length);
        
        size_t _read(char *res, size_t length);
    public:
        
        ~CircleBuffer();
        static CircleBuffer *Create(size_t length);
        
        void clean();
        
        size_t getWriteAvailableBytesSize();
        
        size_t write(const char *pRes, size_t length);
        
        size_t read(char *res, size_t length);
    };
}
#endif /* AirCircleBuffer_hpp */
