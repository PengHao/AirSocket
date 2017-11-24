//
//  AirOperation.cpp
//  AirSocket
//
//  Created by peng hao on 2017/11/21.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <stdio.h>
#include "AirOperation.h"

namespace AirCpp{
    
    Operation::Operation(const Operation &op) {
        
    }
    
    Operation::Operation() :
    concurrence_index(0),
    func_type(0) {
        serial_func = nullptr;
        concurrence_func = nullptr;
    }
    
    int Operation::init(std::function<void()> _func)
    {
        
        serial_func = _func;
        return 0;
    }
    int Operation::init(std::function<void(int)> _func)
    {
        concurrence_func = _func;
        return 0;
    }
    
    void Operation::excute() const {
        if (concurrence_func) {
            concurrence_func(concurrence_index);
        } else {
            serial_func();
        }
    }
    
    Operation::~ Operation() {
        serial_func = nullptr;
        concurrence_func = nullptr;
    }
}
