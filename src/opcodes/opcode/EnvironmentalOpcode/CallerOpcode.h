#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class CallerOpcode : public EnvironmentalOpcode{
    public:
        CallerOpcode(long offset) : EnvironmentalOpcode(OpcodeID::CALLER){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};