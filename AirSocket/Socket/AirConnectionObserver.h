//
//  AirConnectionObserver.h
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/18.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirConnectionObserver_h
#define AirConnectionObserver_h

#include <stdio.h>
#include <iostream>
#include "AirPackage.h"
#include "AirConnection.h"


#define TEMP_BUFFER_SIZE 1024
namespace AirCpp {
    class ConnectionObserver {
    public:
        virtual void onReadable(const Connection *) = 0;
        virtual void onTimeOut(const Connection *) = 0;
    };
}
#endif /* AirConnectionObserver_h */
