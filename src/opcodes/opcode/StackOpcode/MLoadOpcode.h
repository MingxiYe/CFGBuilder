#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class MLoadOpcode : public StackOpcode{
    public:
        MLoadOpcode(long offset) : StackOpcode(OpcodeID::MLOAD){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 1;
        }
};