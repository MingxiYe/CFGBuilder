#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class MSizeOpcode : public StackOpcode{
    public:
        MSizeOpcode(long offset) : StackOpcode(OpcodeID::MSIZE){
            this->offset = offset;
        }

        int getStackConsumed() const{
            return 0;
        }
};