//
//  AirFormatDataIO.h
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/20.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirConnectionIO_h
#define AirConnectionIO_h

#include <stdio.h>
#include <functional>
#include "AirConnection.h"
#include "AirPackage.h"
namespace AirCpp {
    typedef std::function< void (const FormatedData *)> ReseivePackageHandler;
    
    class FormatDataIO {
    public:
        virtual void fillData(unsigned long long len, char *data, ReseivePackageHandler reseiveHandler) = 0;
        virtual ~FormatDataIO(){};
    };
    
    class ConnectionIOFactory {
    public:
        virtual FormatDataIO *create() = 0;
    };
}
#endif /* AirConnectionIO_h */
