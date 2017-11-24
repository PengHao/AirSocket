//
//  SessionManager.h
//  AirSocket
//
//  Created by peng hao on 2017/11/22.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef SessionManager_h
#define SessionManager_h

#include <stdio.h>
#include "AirSession.h"

namespace AirCpp {
    class ConnectionManager;
    class Connection;
    
    class SessionManager : public ConnectionObserver{
        friend Server;
    private:
        std::map<int, Session *> m_mapSessionMap;
        SessionObserver *m_pSessionObserver;
    protected:
        
        void onReadable(const Connection *pConnection);
        
        void onTimeOut(const Connection *pConnection);
        
        void onSendFaild(const Connection *pConnection);
        
        void onReadFaild(const Connection *pConnection);
        
        bool needObserving(const Connection *pConnection);
        
        void willBeDestroy(const Connection *pConnection);
        
        Session *getSession(const Connection *pConnection) {
            return m_mapSessionMap[pConnection->getHandle()];
        }
    public:
        Session *create(const Connection *pConnection);
        
        void destroySession(Session *pSession);
        
        SessionManager(SessionObserver *pSessionObserver);
        
        bool send(Session *pSession, const FormatedData *package);
        
        bool read(Session *pSession, ReseivePackageHandler reseiveHandler);
        
        
        virtual ~SessionManager();
    };
}

#endif /* SessionManager_h */