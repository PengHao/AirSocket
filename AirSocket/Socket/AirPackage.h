//
//  AirPackage.hpp
//  Socket
//
//  Created by 彭浩 on 16/7/26.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#ifndef AirPackage_hpp
#define AirPackage_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
    
    
    class Package {
    public:
        unsigned long long m_ullSize;
        unsigned char *m_pData;
        unsigned long long m_ullSettedSize;
    public:
        Package();
        
        Package(const std::string &data);
        
        ~Package();
    };
    
}
#endif /* AirPackage_hpp */

