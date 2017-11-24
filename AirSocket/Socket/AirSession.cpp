//
//  AirSession.cpp
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/18.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include "AirSession.h"
namespace AirCpp {

    void Session::setUid(long long uid) {
        m_llUid = uid;
    }
    
    Session::Session(const Connection *pConnection):
    m_pConnection(pConnection),
    m_llUid(0)
    {
        
    }
    const Connection *Session::getConnection() {
        return m_pConnection;
    }
    
    long long Session::getUid() {
        return m_llUid;
    }

}
