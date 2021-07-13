#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class SelfBalanceOpcode : public EnvironmentalOpcode{
    public:
        SelfBalanceOpcode(long offset) : EnvironmentalOpcode(OpcodeID::SELFBALANCE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};