#include<iostream>
#ifndef _ENVIRONMENTALOPCODE_H
#define _ENVIRONMENTALOPCODE_H
#include "../EnvironmentalOpcode.h"
#endif

using namespace std;

class BalanceOpcode : public EnvironmentalOpcode{
    public:
        BalanceOpcode(long offset) : EnvironmentalOpcode(OpcodeID::BALANCE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 1;
        }
};