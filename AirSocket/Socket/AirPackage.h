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
    
    class FormatedData {
    public:
        virtual bool serial(std::string &serilazeString)  const = 0;
        virtual bool deserial(std::string &deserilazeString) = 0;
        virtual bool getContent(std::string &contentData) const = 0;
        virtual bool setContent(const std::string &contentData) = 0;
    };
    
    class Package : public FormatedData {
    public:
        size_t m_ulSize;
        unsigned char *m_pData;
        size_t m_ulFilledSize;
    public:
        Package();
        
        Package(const std::string &data);
        
        bool serial(std::string &serilazeString) const;
        
        bool deserial(std::string &serilazeString);
        
        bool getContent(std::string &contentData) const;
        
        bool setContent(const std::string &contentData);
        ~Package();
    };
    
}
#endif /* AirPackage_hpp */

