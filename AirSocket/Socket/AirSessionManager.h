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
    class ConnectionObserver;
    class Connection;
    class SessionManager : public SessionObserver{
        friend Server;
    private:
        std::map<int, Session *> m_mapSessionMap;
        ConnectionObserverCenter *m_pConnectionOberverCenter;
    protected:
        SessionManager();
        
        virtual void onReadable(Session *) = 0;
        virtual void onTimeOut(Session *) = 0;
        virtual void onHandleNewSession(Session *) = 0;
        virtual void onSendFaild(Session *) = 0;
        virtual void onReadFaild(Session *) = 0;
        
        Session *create(Connection *pConnection);
    public:
        
        
        virtual ~SessionManager();
    };
}

#endif /* SessionManager_h */
