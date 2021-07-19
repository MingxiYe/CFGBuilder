#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class GasOpcode : public StackOpcode{
    public:
        GasOpcode(long offset) : StackOpcode(OpcodeID::GAS){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};