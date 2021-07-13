#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class ReturnDataCopyOpcode : public EnvironmentalOpcode{
    public:
        ReturnDataCopyOpcode(long offset) : EnvironmentalOpcode(OpcodeID::RETURNDATACOPY){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 3;
        }
};