#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class CallDataLoadOpcode : public EnvironmentalOpcode{
    public:
        CallDataLoadOpcode(long offset) : EnvironmentalOpcode(OpcodeID::CALLDATALOAD){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 1;
        }
};