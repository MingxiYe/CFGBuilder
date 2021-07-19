#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class PCOpcode : public StackOpcode{
    public:
        PCOpcode(long offset) : StackOpcode(OpcodeID::PC){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};