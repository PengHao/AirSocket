//
//  AirConnectionIO.h
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
    typedef std::function< void (const DataFormat *)> ReseivePackageHandler;
    class ConnectionIO {
    public:
        virtual bool send(const DataFormat *package, Connection *pConnection) = 0;
        virtual bool read(ReseivePackageHandler reseiveHandler, Connection *pConnection) = 0;
        virtual ~ConnectionIO(){};
    };
}
#endif /* AirConnectionIO_h */
