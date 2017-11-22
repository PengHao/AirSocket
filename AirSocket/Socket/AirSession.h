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
#include "AirConnectionObserverCenter.h"
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
        virtual ~SessionObserver(){};
    };
    
    class Session : public ConnectionObserver{
        friend SessionManager;
    protected:
        long long m_llUid;
        Connection *m_pConnection;
        SessionObserver *m_pSessionObserver;
        ConnectionIO *m_pConnectionIO;
        
        void onReadable(const Connection *);
        
        void onTimeOut(const Connection *);
        
        void onSendFaild(const Connection *);
        
        void onReadFaild(const Connection *);
        
    public:
        long long getUid();
        
        void setUid(long long uid);
        
        Session(Connection *pConnection, SessionObserver *pSessionObserver);
        
        void setConnectionIO(ConnectionIO *pConnectionIO);
        
        bool send(const DataFormat *package);
        
        bool read(ReseivePackageHandler reseiveHandler);
        
        ~Session() {
            delete m_pConnection;
            delete m_pSessionObserver;
            delete m_pConnectionIO;
        }
    };
    
}

#endif /* AirSession_h */
