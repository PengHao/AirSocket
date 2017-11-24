//
//  AirConnectionPackageIO.h
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/18.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirConnectionPackageIO_h
#define AirConnectionPackageIO_h

#include <stdio.h>
#include <iostream>
#include "AirPackage.h"
#include "AirConnection.h"
#include "AirConnectionObserver.h"

#define TEMP_BUFFER_SIZE 1024
namespace AirCpp {
    
    class ConnectionPackageIO : public FormatDataIO {
        class ConnectionObserverCenter;
        class Listener;
        class Server;
        
    private:
        typedef std::function<void(const Package *package)> FillPackageCallBack;
        
        Package * pCurrentPackage;
        
    public:
        
        ConnectionPackageIO();
        
        ~ConnectionPackageIO();
        
        void fillData(unsigned long long len, char *data, ReseivePackageHandler reseiveHandler);
        
    };
}

#endif /* AirConnectionPackageIO_h */
