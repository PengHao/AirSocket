//
//  AirSocketMac.cpp
//  AirSocketMac
//
//  Created by peng hao on 2017/11/29.
//  Copyright © 2017年 peng hao. All rights reserved.
//

#include <iostream>
#include "AirSocketMac.hpp"
#include "AirSocketMacPriv.hpp"

void AirSocketMac::HelloWorld(const char * s)
{
    AirSocketMacPriv *theObj = new AirSocketMacPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void AirSocketMacPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

