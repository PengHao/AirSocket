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
        virtual void onTimeOut(Session *pSession, bool *pNeedDisConnect) = 0;
        virtual void onHandleNewSession(Session *) = 0;
        virtual ~SessionObserver(){};
    };
    
    class Session {
        friend SessionManager;
    protected:
        long long m_llUid;
        Connection *m_pConnection;
        SessionObserver *m_pSessionObserver;
        ConnectionIO *m_pConnectionIO;
        
    public:
        void setUid(long long uid);
        
        Session(Connection *pConnection, SessionObserver *pSessionObserver);
        
    public:
        long long getUid();
        
        Connection* getConnection();
        
        void setConnectionIO(ConnectionIO *pConnectionIO);
        
        bool send(const Package *package);
        
        void read(ReseivePackageHandler reseiveHandler);
        
        ~Session() {
            delete m_pConnection;
            delete m_pSessionObserver;
            delete m_pConnectionIO;
        }
    };
    
    class ConnectionObserver;
    class Connection;
    class SessionManager : public ConnectionObserver{
        friend Server;
    private:
        ConnectionObserverCenter *m_pConnectionOberverCenter;
        std::map<int, Session *> m_mapSessionMap;
    protected:
        SessionManager();
        
        void onReadable(const Connection *pConnection);
        
        void onTimeOut(const Connection *pConnection);
        
        Session *getSession(const Connection *pConnection);
        
        Session *create(Connection *pConnection, SessionObserver *pSessionObserver);
    public:
        static SessionManager *_defaultSessionManager;
        static SessionManager *defaultSessionManager();
        
        
        ~SessionManager();
    };
}

#endif /* AirSession_h */
