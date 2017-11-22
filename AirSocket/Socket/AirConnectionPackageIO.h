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
#include "AirConnectionIO.h"
#define TEMP_BUFFER_SIZE 1024
namespace AirCpp {
    
    class ConnectionPackageIO : public ConnectionIO {
        class ConnectionObserverCenter;
        class Listener;
        class Server;
        
    private:
        typedef std::function<void(const Package *package)> FillPackageCallBack;
        char m_strTempBuffer[TEMP_BUFFER_SIZE];
        Package * pCurrentPackage;
        
        
        void fillData(unsigned long long len, char *data, FillPackageCallBack handleFilledPackage);
    public:
        
        ConnectionPackageIO();
        
        ~ConnectionPackageIO();
        
        bool send(const DataFormat *package, Connection *pConnection);
        
        bool read(ReseivePackageHandler reseiveHandler, Connection *pConnection);
    };
}

#endif /* AirConnectionPackageIO_h */
