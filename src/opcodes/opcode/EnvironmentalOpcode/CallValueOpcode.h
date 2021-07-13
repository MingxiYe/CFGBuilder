#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class CallValueOpcode : public EnvironmentalOpcode{
    public:
        CallValueOpcode(long offset) : EnvironmentalOpcode(OpcodeID::CALLVALUE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};