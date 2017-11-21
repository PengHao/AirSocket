//
//  AirSocket.cpp
//  PCMPlayerServer
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include "AirSocket.h"
namespace AirCpp {
    
    Socket::Socket( const Socket &s ): m_iSocketHandle(s.m_iSocketHandle) {
        m_pTarget_addr = (sockaddr_in *)malloc(sizeof(sockaddr_in));
        memcpy(m_pTarget_addr, s.m_pTarget_addr, sizeof(sockaddr_in));
    }
    
    Socket::Socket(long timeout):
    m_iSocketHandle(-1),
    m_pTarget_addr(NULL)
    {
        m_pTarget_addr = (sockaddr_in *)malloc(sizeof(sockaddr_in));
        memset(m_pTarget_addr, 0, sizeof(sockaddr_in));
        struct sigaction action;
        action.sa_handler = handle_pipe;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0;
        sigaction(SIGPIPE, &action, NULL);
    }
    
    Socket::~Socket(){
        close();
        free(m_pTarget_addr);
    }
    
    void Socket::handle_pipe(int sig)
    {
        //不做任何处理即可
        perror("Some socket connection is timeout!\n");
        printf("getpid = %d\n", getpid());
    }
    
    int Socket::connect(const std::string &host, int port){
        const char *ip_addr = get_ip(host);
        if (NULL == ip_addr) {
            printf("cannot find ip from host %s ,please check your url or network! \n", host.c_str());
            return -1;
        }
        
        m_pTarget_addr->sin_addr.s_addr = inet_addr(ip_addr);
        m_pTarget_addr->sin_port = htons(port);
        bzero(&(m_pTarget_addr->sin_zero), 8);
        
        if (0 != ::connect(m_iSocketHandle, (const struct sockaddr *)(m_pTarget_addr), sizeof(const struct sockaddr))) {
            perror("failed to connect socket\n");
            ::close(m_iSocketHandle);
            return(-1);                                             /* bind address to socket */
        }
        return 0;
    }
    
    int Socket::bind(unsigned short portnum){
        hostent * h = get_host_info();
        if (h == NULL) {
            printf("failed to get gethostbyname\n");
            return -1;
        }
        m_pTarget_addr->sin_family= h->h_addrtype;                     /* this is our host address */
        m_pTarget_addr->sin_port= htons(portnum);                       /* this is our port number */
        
        if (0 != ::bind(m_iSocketHandle, (const struct sockaddr *)(m_pTarget_addr), sizeof(const struct sockaddr))) {
            perror("failed to bind socket\n");
            ::close(m_iSocketHandle);
            return(-1);                                             /* bind address to socket */
        }
        return 0;
    }
    
    int Socket::listen(unsigned int backlog) {
        
        if (::listen(m_iSocketHandle, backlog)<0) {
            perror("listen socket failed\n");
            return -1;
        }
        return 0;
    }
    
    
    int Socket::accept(sockaddr *client_addr, socklen_t *client_size)
    {
        printf("accept connection\n");
        int t = -1;                                                          /* socket of connection */
        if ((t = ::accept(m_iSocketHandle, client_addr, client_size)) < 0){
            t = -1;
        }
        return(t);
    }
    
    int Socket::init(int domainType, int dataType, int protocol){
        m_iSocketHandle = socket(domainType, dataType, protocol);
        if (m_iSocketHandle == -1) {
            return -1;
        }
        m_pTarget_addr->sin_family = domainType;
        return 0;
    }
    
    int Socket::init(const int socket_handle, const struct sockaddr *client_addr, const socklen_t *client_size){
        memcpy(m_pTarget_addr, client_addr, sizeof(sockaddr_in));
        m_iSocketHandle = socket_handle;
        return 0;
    }
    
    long long Socket::send(const char *c_data, long long length){
        long long dataSended = (long long)::send(m_iSocketHandle, c_data, length, 0);
        return dataSended;
    }
    
    long long Socket::read(char *c_data, long long length){
        return (long long)::read(m_iSocketHandle, c_data, length);
    }
    
    /**
     *    关闭连接
     */
    void Socket::close()
    {
        ::close(m_iSocketHandle);
    }
    
    /**
     *    获取网络的ip地址
     *
     *    @param     _host     网络名称、网址
     *
     *    @return    返回ip地址
     */
    const char * Socket::get_ip(const std::string & _host)
    {
        struct hostent *host = gethostbyname(_host.c_str());
        if(!host){
            herror("resolv");
            return NULL;
        }
        struct in_addr **list = (struct in_addr **)host->h_addr_list;
        return inet_ntoa(*list[0]);
    }
    
    /**
     *    获取网络的信息
     *
     *    @return    返回主机信息
     */
    hostent *Socket::get_host_info(){
        char   myname[MAXHOSTNAME+1];
        gethostname(myname, MAXHOSTNAME);               /* who are we? */
        return(gethostbyname(myname));                     /* get our address info */
    }
    
}
