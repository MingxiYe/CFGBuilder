#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class CallDataSizeOpcode : public EnvironmentalOpcode{
    public:
        CallDataSizeOpcode(long offset) : EnvironmentalOpcode(OpcodeID::CALLDATASIZE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};