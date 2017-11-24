//
//  AirSession.h
//  PCMStramPlayer
//
//  Created by peng hao on 2017/11/18.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirSession_h
#define AirSession_h

#include <stdio.h>
#include <map>
#include "AirConnection.h"
#include "AirConnectionPackageIO.h"
#include "AirConnectionObserver.h"
#include "AirConnectionManager.h"
namespace AirCpp {
    class Session;
    class SessionManager;
    class SessionObserver {
    public:
        virtual void onReadable(Session *) = 0;
        virtual void onTimeOut(Session *) = 0;
        virtual void onHandleNewSession(Session *) = 0;
        virtual void onSendFaild(Session *) = 0;
        virtual void onReadFaild(Session *) = 0;
        virtual bool needObserving(Session *) = 0;
        virtual void willBeDestroy(Session *) = 0;
        virtual ~SessionObserver(){};
    };
    
    class Session{
        friend SessionManager;
    protected:
        long long m_llUid;
        const Connection *m_pConnection;
        
    public:
        long long getUid();
        
        void setUid(long long uid);
        
        const Connection *getConnection();
        
        Session(const Connection *pConnection);
        
        ~Session() {
            delete m_pConnection;
        }
    };
    
}

#endif /* AirSession_h */
