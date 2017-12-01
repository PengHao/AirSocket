//
//  AirSocketDefine.h
//  AirSocket
//
//  Created by peng hao on 2017/11/29.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#ifndef AirSocketDefine_h
#define AirSocketDefine_h

#ifdef DEBUG_LOG
#include <time.h>
#define LOG_INFO(format, ...) { \
    char buffer[1024] = {0}; \
    snprintf(buffer, 1024, format, ##__VA_ARGS__); \
    printf("Time:[%s] %s", __TIME__, buffer); \
}

#else
#define LOG_INFO(format, ...)  
#endif

#endif /* AirSocketDefine_h */
