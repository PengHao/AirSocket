//
//  AirSocketStream.h
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/9.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirSocketStream_h
#define AirSocketStream_h

#include <stdio.h>
#include "AirConnection.h"
#include <istream>

namespace AirCpp {
    class StreamConnection : std::istream {
    private:
        Connection *connection;
        
    protected:
        
//        AirSocketStream *Create(int domainType, int dataType, int protocol) {
//            AirSocketStream *conn = new AirSocketStream(domainType, dataType, protocol);
//            return conn;
//        }
//        
//        AirSocketStream(int domainType, int dataType, int protocol):
//        AirCpp::Connection(domainType, dataType, protocol){
//            
//        }
    };
    
}

#endif /* AirSocketStream_h */
