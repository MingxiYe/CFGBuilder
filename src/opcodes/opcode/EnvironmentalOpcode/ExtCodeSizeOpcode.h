#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class ExtCodeSizeOpcode : public EnvironmentalOpcode{
    public:
        ExtCodeSizeOpcode(long offset) : EnvironmentalOpcode(OpcodeID::EXTCODESIZE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 1;
        }
};