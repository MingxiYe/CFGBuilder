#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class CallDataCopyOpcode : public EnvironmentalOpcode{
    public:
        CallDataCopyOpcode(long offset) : EnvironmentalOpcode(OpcodeID::CALLDATACOPY){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 3;
        }

        int getStackGenerated() const{
            return 0;
        }
};