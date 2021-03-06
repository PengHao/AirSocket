//
//  AirOperation.h
//  AirCpp
//
//  Created by Penghao on 14-2-25.
//  Copyright (c) 2014年 PengHao. All rights reserved.
//

#ifndef __AirCpp__AirOperation__
#define __AirCpp__AirOperation__

#include <iostream>
#include <functional>
namespace AirCpp{
    /**
     *	多线程的操作，将对象和相应需要进行调用的方法封装到其中
     */
    class Operation {
    friend class AirQueue;
    protected:
        int concurrence_index;
        int func_type;
        std::function<void()> serial_func;
        std::function<void(int)> concurrence_func;
    public:
        
        Operation(const Operation &op);
        
        Operation();
        
        int init(std::function<void()> _func);
        
        int init(std::function<void(int)> _func);
        
        void excute() const;
        
        ~ Operation();
    };
}

#endif /* defined(__AirCpp__AirOperation__) */
