#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class SLoadOpcode : public StackOpcode{
    public:
        SLoadOpcode(long offset) : StackOpcode(OpcodeID::SLOAD){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 1;
        }
};