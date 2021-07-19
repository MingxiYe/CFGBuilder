#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class ReturnDataSizeOpcode : public EnvironmentalOpcode{
    public:
        ReturnDataSizeOpcode(long offset) : EnvironmentalOpcode(OpcodeID::RETURNDATASIZE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};