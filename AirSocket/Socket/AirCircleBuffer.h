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
namespace AirCpp {
    class TPCircularBufferContainor;
    class CircleBuffer {
    protected:
        TPCircularBufferContainor *m_pTPCircularBufferContainor;
        
        int32_t m_iSize;
        
        CircleBuffer(int32_t size);
    public:
        static CircleBuffer* Create(int32_t size);
        
        int32_t read(char *c_data, int32_t length);
        
        int32_t getWriteAvailableBytesSize();
        
        int32_t write(const char *c_data, int32_t length);
    };
}
#endif /* AirCircleBuffer_hpp */
