//
//  AirConnectionManagerDelegate.h
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/18.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirConnectionManagerDelegate_h
#define AirConnectionManagerDelegate_h

#include <stdio.h>
#include <iostream>
#include "AirPackage.h"
#include "AirConnection.h"


#define TEMP_BUFFER_SIZE 1024
namespace AirCpp {
    class ConnectionManager;
    class ConnectionManagerDelegate {
    public:
        virtual void onReadable(const Connection *) = 0;
        virtual void onTimeOut(const Connection *) = 0;
        virtual void onSendFaild(const Connection *) = 0;
        virtual void onReadFaild(const Connection *) = 0;
        virtual void willBeDestroy(const Connection *) = 0;
        virtual bool needObserving(const Connection *) = 0;
        virtual void willBeTerminated(ConnectionManager *) = 0;
    };
}
#endif /* AirConnectionManagerDelegate_h */
