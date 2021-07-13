#include<iostream>
#ifndef _STACKOPCODE_H
#define _STACKOPCODE_H
#include "../StackOpcode.h"
#endif

using namespace std;

class PopOpcode : public StackOpcode{
    public:
        PopOpcode(long offset) : StackOpcode(OpcodeID::POP){
            this->offset = offset;
        }

        int getStackGenerated() const{
            return 0;
        }

        int getStackConsumed() const{
            return 1;
        }
};